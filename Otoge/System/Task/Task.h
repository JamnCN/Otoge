#pragma once
#include "../../Util/Debug/Logger.h"

class Task
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
    bool isAutoUpdateChildren = true; // �q�^�X�N��Update�������Ŏ��s���邩

    std::vector<std::shared_ptr<Task>> children; // �q�^�X�N
    std::vector<std::shared_ptr<Task>> childrenQueues;

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
    bool AddChildTask(const std::shared_ptr<Task> &task);
	std::vector<std::shared_ptr<Task>>& GetChildren();
	std::vector<std::shared_ptr<Task>>& GetChildrenQueues();
    
};
