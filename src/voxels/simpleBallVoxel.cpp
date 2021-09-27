#include "voxels/simpleBallVoxel.h"

SimpleBallVoxel::SimpleBallVoxel()
{
    radius = 0.1;
    this->startPos = glm::vec3(-0.5, -0.7, -1);
    float len = radius * 2 * sqrt(3);
    this->center = this->startPos + glm::vec3(len / 2);
    this->xLen = len;
    this->yLen = len;
    this->zLen = len;

    this->xCount = 50;
    this->yCount = 50;
    this->zCount = 50;

    this->deltaX = xLen / xCount;
    this->deltaY = yLen / yCount;
    this->deltaZ = zLen / zCount;

    this->model = glm::mat4(1.0F);
    this->view = globalCamera.GetViewMatrix();
    this->projection = glm::perspective(glm::radians(45.0f), (float)(800)/(float)(600), 0.1f, 100.0f);

    this->boundingBox = std::make_shared<AABB>(startPos, startPos + glm::vec3(xLen, yLen, zLen));
    this->voxelHitResult = std::make_shared<VoxelHitResult>();
    this->moveAble = true;

    genVertices();
    genBuffers();
    genShaders();
}

SimpleBallVoxel::~SimpleBallVoxel()
{
}

bool SimpleBallVoxel::rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r)
{
    return false;
}

bool SimpleBallVoxel::voxelOverlap(shared_ptr<VoxelBase> voxel, shared_ptr<AABB> box)
{
    if(!box->intersects(voxel->boundingBox))
    {
        voxelHitResult->setStartPenetrating(false);
        return false;
    }

    auto startPos = box->getBoxMin();
    auto endPos = box->getBoxMax();

    glm::ivec3 indexI = (startPos - voxel->startPos) / glm::vec3(voxel->xLen / voxel->xCount, voxel->yLen / voxel->yCount, voxel->zLen / voxel->zCount);
    glm::ivec3 indexJ = (endPos - voxel->startPos) / glm::vec3(voxel->xLen / voxel->xCount, voxel->yLen / voxel->yCount, voxel->zLen / voxel->zCount);

    //when run here, it means boundingBox is overlap, so there must be some [i, j, k]'s in voxel's range
    //here[i, j, k] means the ith cut-off face in x-direction, y means in y-direction, z means in z-direction
    indexI = glm::clamp(indexI, glm::ivec3(0), glm::ivec3(voxel->xCount, voxel->yCount, voxel->zCount));
    indexJ = glm::clamp(indexJ, glm::ivec3(0), glm::ivec3(voxel->xCount, voxel->yCount, voxel->zCount));

    auto sPos = glm::vec3(model * glm::vec4(startPos, 1.0f));
    auto ePos = sPos + glm::vec3(xLen, yLen, zLen);

#ifdef DEBUG_VOXELOVERLAP
    std::cout<<"===========================voxelOverlap==========================="<<std::endl;
    std::cout<<"startPos: "<<sPos.x<<" "<<sPos.y<<" "<<sPos.z<<std::endl;
    std::cout<<"endPos: "<<ePos.x<<" "<<ePos.y<<" "<<ePos.z<<std::endl;
    std::cout<<"indexI: "<<indexI.x<<" "<<indexI.y<<" "<<indexI.z<<std::endl;
    std::cout<<"indexJ: "<<indexJ.x<<" "<<indexJ.y<<" "<<indexJ.z<<std::endl;
    std::cout<<"===========================voxelOverlap==========================="<<std::endl<<std::endl;
#endif
    //here [i, j, k] means the ith sub-voxel in x-direction, etc.
    //note that x cut-off face is one more than xCount, so does y cut-off yCount etc.
    for(int i = indexI.x; i <= indexJ.x; ++i)
        for(int j = indexI.y; j <= indexJ.y; ++j)
            for(int k = indexI.z; k <= indexJ.z; ++k)
            {
                if(voxel->types[voxel->getIndex(i, j, k)] != 0)
                {
                    voxelHitResult->setPenetrationDepth(getMaxPenetration(i, j, k, voxel, startPos, endPos));
                    voxelHitResult->setStartPenetrating(true);
                    return true;
                }
            }

    voxelHitResult->setStartPenetrating(false);
    return false;
}

float SimpleBallVoxel::getMaxPenetration(int i, int j, int k, shared_ptr<VoxelBase> voxel, glm::vec3 startPos, glm::vec3 endPos)
{
    int positiveX = 1;
    int positiveY = 1;
    int positiveZ = 1;
    if(frontDirection.x < 0)
        positiveX = 0;
    if(mState == MoveState::DOWN)
        positiveY = 0;
    if(frontDirection.z < 0)
        positiveZ = 0;

    glm::vec3 colliPoint = endPos;
    glm::vec3 voxelDelta = glm::vec3(voxel->xLen, voxel->yLen, voxel->zLen) / glm::vec3(voxel->xCount, voxel->yCount, voxel->zCount);
    glm::vec3 voxelPoint = voxel->startPos + glm::vec3(i * voxelDelta.x, j * voxelDelta.y, k * voxelDelta.z);

    if(!positiveX)
    {
        colliPoint.x = startPos.x;
        voxelPoint.x += voxelDelta.x;
    }
    if(!positiveY)
    {
        colliPoint.y = startPos.y;
        voxelPoint.y += voxelDelta.y;
    }
    if(!positiveZ)
    {
        colliPoint.z = startPos.z;
        voxelPoint.z += voxelDelta.z;
    }

#ifdef DEBUG_VOXELOVERLAP
    std::cout<<"===========================getMaxPenetration==========================="<<std::endl;
    std::cout<<"startPos: "<<startPos.x<<" "<<startPos.y<<" "<<startPos.z<<std::endl;
    std::cout<<"endPos: "<<endPos.x<<" "<<endPos.y<<" "<<endPos.z<<std::endl;
    std::cout<<"colliPoint: "<<colliPoint.x<<" "<<colliPoint.y<<" "<<colliPoint.z<<std::endl;
    std::cout<<"voxelPoint: "<<voxelPoint.x<<" "<<voxelPoint.y<<" "<<voxelPoint.z<<std::endl;
    std::cout<<"===========================getMaxPenetration==========================="<<std::endl<<std::endl;
#endif

    float xPen = glm::abs(voxelPoint.x - colliPoint.x);
    float yPen = glm::abs(voxelPoint.y - colliPoint.y);
    float zPen = glm::abs(voxelPoint.z - colliPoint.z);

    return glm::min(xPen, glm::min(yPen, zPen));
}

void SimpleBallVoxel::updateView(glm::vec2 deltaDirec)
{}

void SimpleBallVoxel::updateModel(float deltaTime, Direction d)
{
    glm::vec3 deltaMovement;
    if(d == Direction::BACKWARD)
    {
        deltaMovement = -moveSpeed * deltaTime * glm::vec3(upDirection);
    }
    if(d == Direction::FORWARD)
    {
        deltaMovement = moveSpeed * deltaTime * glm::vec3(upDirection);
    }
    if(d == Direction::LEFT)
    {
        deltaMovement = moveSpeed * deltaTime * glm::vec3(leftDirection);
    }
    if(d == Direction::RIGHT)
    {
        deltaMovement = -moveSpeed * deltaTime * glm::vec3(leftDirection);
    }
    if(d == Direction::UP)
    {
        deltaMovement = moveSpeed * deltaTime * glm::vec3(0, 1, 0);
    }
    if(d == Direction::DOWN)
    {
        deltaMovement = -moveSpeed * deltaTime * glm::vec3(0, 1, 0);
    }

    updateModel(glm::translate(model, deltaMovement));
}

void SimpleBallVoxel::updateModel(glm::mat4 m)
{
    model = m;
    glm::vec3 newStartPos = glm::vec3(model * glm::vec4(startPos, 1.0));
    boundingBox = std::make_shared<AABB>(newStartPos, newStartPos + glm::vec3(xLen, yLen, zLen));
    shaderProgram->use();
    shaderProgram->setMat4("model", model);
}

void SimpleBallVoxel::handleGravity(float time, std::vector<std::shared_ptr<VoxelBase> > staticVoxls)
{
    //simple move down
    auto deltaMovement = -time * fallSpeed * glm::vec3(0, 1, 0);
    glm::mat4 tmpModel = glm::translate(model, deltaMovement);
    auto tmpStartPos = glm::vec3(tmpModel * glm::vec4(startPos, 1.0f));
    auto tmpBoundingBox = std::make_shared<AABB>(tmpStartPos, tmpStartPos + glm::vec3(xLen, yLen, zLen));
    mState = MoveState::DOWN;

    for(auto v : staticVoxls)
    {
        if(!voxelOverlap(v, tmpBoundingBox))
        {
            continue;
        }
    }

    if(voxelHitResult->getStartPenetrating())
    {
        //move back penetrationDepth + epslion
        float backDistance = voxelHitResult->getPenetrationDepth() + DISTANCE_EPSLION;
        tmpModel = glm::translate(tmpModel, -backDistance * glm::normalize(deltaMovement));
    }

    updateModel(tmpModel);
}

void SimpleBallVoxel::move(glm::vec3 deltaMovement, std::vector<std::shared_ptr<VoxelBase> > staticVoxls)
{
    glm::mat4 tmpModel = glm::translate(model, deltaMovement);
    auto tmpStartPos = glm::vec3(tmpModel * glm::vec4(startPos, 1.0f));
    auto tmpBoundingBox = std::make_shared<AABB>(tmpStartPos, tmpStartPos + glm::vec3(xLen, yLen, zLen));
    if(deltaMovement.y > 0)
        mState = MoveState::UP;
    if(deltaMovement.y < 0)
        mState = MoveState::DOWN;

    for(auto v : staticVoxls)
    {
        if(!voxelOverlap(v, tmpBoundingBox))
        {
            continue;
        }
    }

    if(voxelHitResult->getStartPenetrating())
    {
        //move back penetrationDepth + epslion
        float backDistance = voxelHitResult->getPenetrationDepth() + DISTANCE_EPSLION;
        tmpModel = glm::translate(tmpModel, -backDistance * glm::normalize(deltaMovement));
    }

    updateModel(tmpModel);
}

void SimpleBallVoxel::draw()
{
    shaderProgram->use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void SimpleBallVoxel::pushSubVoxelPositions(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd)
{
    int size = positions.size() / 3;

    //1.push positions
    positions.push_back(xStart); positions.push_back(yStart); positions.push_back(zStart);
    positions.push_back(xStart); positions.push_back(yEnd); positions.push_back(zStart);
    positions.push_back(xEnd); positions.push_back(yEnd); positions.push_back(zStart);
    positions.push_back(xEnd); positions.push_back(yStart); positions.push_back(zStart);

    positions.push_back(xStart); positions.push_back(yStart); positions.push_back(zEnd);
    positions.push_back(xStart); positions.push_back(yEnd); positions.push_back(zEnd);
    positions.push_back(xEnd); positions.push_back(yEnd); positions.push_back(zEnd);
    positions.push_back(xEnd); positions.push_back(yStart); positions.push_back(zEnd);

    //push indexes
    //back
    indices.push_back(size + 0); indices.push_back(size + 1); indices.push_back(size + 2);
    indices.push_back(size + 2); indices.push_back(size + 3); indices.push_back(size + 0);

    //front
    indices.push_back(size + 6); indices.push_back(size + 5); indices.push_back(size + 4);
    indices.push_back(size + 4); indices.push_back(size + 7); indices.push_back(size + 6);

    //left
    indices.push_back(size + 4); indices.push_back(size + 5); indices.push_back(size + 1);
    indices.push_back(size + 1); indices.push_back(size + 0); indices.push_back(size + 4);

    //right
    indices.push_back(size + 7); indices.push_back(size + 6); indices.push_back(size + 2);
    indices.push_back(size + 2); indices.push_back(size + 3); indices.push_back(size + 7);

    //top
    indices.push_back(size + 5); indices.push_back(size + 6); indices.push_back(size + 2);
    indices.push_back(size + 2); indices.push_back(size + 1); indices.push_back(size + 5);

    //bottom
    indices.push_back(size + 4); indices.push_back(size + 0); indices.push_back(size + 3);
    indices.push_back(size + 3); indices.push_back(size + 7); indices.push_back(size + 4);
}

void SimpleBallVoxel::genVertices()
{
    types = vector<int>(xCount * yCount * zCount, 0);
    for(int i = 0; i < xCount; ++i)
        for(int j = 0; j < yCount; ++j)
            for(int k = 0; k < zCount; ++k)
            {
                float xStart = startPos.x + i * deltaX;
                float yStart = startPos.y + j * deltaX;
                float zStart = startPos.z + k * deltaX;

                float xEnd = xStart + deltaX;
                float yEnd = yStart + deltaY;
                float zEnd = zStart + deltaZ;

                float xMid = (xStart + xEnd) / 2;
                float yMid = (yStart + yEnd) / 2;
                float zMid = (zStart + zEnd) / 2;

                if(glm::dot(glm::vec3(xMid, yMid, zMid) - center, glm::vec3(xMid, yMid, zMid) - center) <= radius * radius)
                {
                    types[getIndex(i, j, k)] = 1;
                    pushSubVoxelPositions(xStart, yStart, zStart, xEnd, yEnd, zEnd);
                }
            }
}

void SimpleBallVoxel::genBuffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

void SimpleBallVoxel::genShaders()
{
    shaderProgram = std::make_shared<Shader>("../shaders/test.vert", "../shaders/test.frag");
    shaderProgram->use();
    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", view);
    shaderProgram->setMat4("projection", projection);
}
