#pragma once
#include "../../Util/Debug/Logger.h"
#include <cstdarg>

class Task : public std::enable_shared_from_this<Task>
{
private:
    //int ID = -1; // �^�X�NID

protected:
    std::string TaskName_ = ""; // ���O

    std::shared_ptr<Logger> Logger_;

    bool isLiving = false; // �����Ă��āA���s�\��(���g�p)
    bool isTerminated = false; // �I������
    bool isInitialized = false; // ����������Ă��邩
    bool isRunning = false; // Update�����s���邩

    float tickSpeed = 1.0f; // �����X�s�[�h (deltaTime���␳�����)

    bool hasLifespan = false; // ���������邩
    float lifespan = 0.f; // ����

public:
    using TaskPointer = std::shared_ptr<Task>;
    using WeakTaskPointer = std::weak_ptr<Task>;

    bool isAutoUpdateChildren = true; // �q�^�X�N��Update�������Ŏ��s���邩

    WeakTaskPointer parentTask; // �e�^�X�N
    std::vector<TaskPointer> children; // �q�^�X�N
    std::vector<TaskPointer> childrenQueues;

    float timerCount = 0.f; // deltaTime�~��

    Task(const std::string &taskName);
    virtual ~Task();

    bool Initialize(int taskID);
    virtual void Update(float deltaTime) = 0;
    
    bool Terminate();
    void Pause();
    void Resume();


    //int GetTaskID() const;

    std::string GetName() const;

    bool CanRunning() const;
    
    bool IsLiving() const;
    bool IsTerminated() const;
    bool IsInit() const;
    bool IsRunning() const;
    
    float GetTickSpeed() const;
    void SetTickSpeed(float tickSpeed);

    bool HasLifespan() const;
    float GetLifespan() const;
    void SetLifespan(float lifespan);

    // �q�^�X�N
    void ChildUpdate(float deltaTime);
    bool AddChildTask(const TaskPointer& task);
	std::vector<TaskPointer>& GetChildren();
	std::vector<TaskPointer>& GetChildrenQueues();
};
