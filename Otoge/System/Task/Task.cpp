#include "Task.h"

Task::Task(const std::string& taskName)
{
    this->TaskName_ = taskName;
    Logger_ = std::make_shared<Logger>(this->TaskName_);
}

Task::~Task()
{
    isLiving = false;
    isRunning = false;
    isInitialized = false;
}

bool Task::Initialize(int taskID)
{
    //ID = taskID;
    isInitialized = true;
    isLiving = true;
    isRunning = true;

    return true;
}

bool Task::Terminate()
{
    isTerminated = true;

    isRunning = false;

    return true;
}

void Task::Pause()
{
    isRunning = false;
}

void Task::Resume()
{
    isRunning = true;
}

std::string Task::GetName() const
{
    return TaskName_;
}


/*int Task::GetTaskID() const
{
    if (!CanRunning()) return -1;

    return ID;
}*/


bool Task::CanRunning() const
{
    return isInitialized && isLiving;
}

bool Task::IsLiving() const
{
    return isLiving;
}

bool Task::IsTerminated() const
{
    return isTerminated;
}

bool Task::IsInit() const
{
    return isInitialized;
}

bool Task::IsRunning() const
{
    return isRunning;
}


float Task::GetTickSpeed() const
{
    if (!CanRunning()) return -1;
    return tickSpeed;
}

void Task::SetTickSpeed(float tickSpeed)
{
    this->tickSpeed = tickSpeed;
}


bool Task::HasLifespan() const
{
    return hasLifespan;
}

float Task::GetLifespan() const
{
    if (!CanRunning()) return -1;

    return lifespan;
}


void Task::SetLifespan(float lifespan)
{
    this->lifespan = lifespan;
}

void Task::ChildUpdate(float deltaTime)
{
    //Logger_->Debug("�q�^�X�N����");
    // �q�^�X�N�ǉ�����
    for (auto& child : childrenQueues)
    {
        children.push_back(child);
        Logger_->Debug(TaskName_ + "�q�^�X�N�ǉ� �^�X�N��:" + std::to_string(children.size()));
    }
    childrenQueues.clear();


    auto task = children.begin();

    for (task; task != children.end(); ++task)
    {
        // �^�C�}�[�X�V
        float fixedDeltaTime = deltaTime * tickSpeed * (*task)->GetTickSpeed();
        (*task)->timerCount += fixedDeltaTime;

        // �^�X�N����
        if ((*task)->CanRunning() && (*task)->IsRunning())
        {
            (*task)->Update(fixedDeltaTime);
            if ((*task)->isAutoUpdateChildren)
                (*task)->ChildUpdate(fixedDeltaTime);
        }

        // �����̏���
        if ((*task)->HasLifespan())
        {
            (*task)->SetLifespan((*task)->GetLifespan() - fixedDeltaTime);
            if ((*task)->GetLifespan() < 0.0f) (*task)->Terminate();
        }

        if ((*task)->IsTerminated())
        {
            task = children.erase(task);
            --task;
        }
    }
}

bool Task::AddChildTask(const std::shared_ptr<Task>& task)
{
    childrenQueues.push_back(task);
    Logger_->Debug(TaskName_ + "�^�X�N�L���[�ǉ� �L���[��:" + std::to_string(childrenQueues.size()));

    return task->Initialize(childrenQueues.size() - 1);
}