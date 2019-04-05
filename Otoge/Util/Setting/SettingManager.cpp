#include "SettingManager.h"

using namespace std;

SettingManager *SettingManager::GlobalSettings_ = nullptr;

bool SettingManager::CanProcess()
{
    return true;
}

SettingManager::SettingManager(const std::string &fileName)
{
    Logger_ = make_shared<Logger>("SettingManager");
    FileName_ = fileName;
}

SettingManager::~SettingManager()
{
}

bool SettingManager::Load(const std::string &fileName, bool autoCreate)
{
    Logger_->Info(fileName + " �ǂݍ��ݒ�...");

    try {
        read_json(fileName, SettingsTree_);
        Logger_->Info("�ǂݍ��ݐ����B");
        return true;
    }catch(boost::property_tree::json_parser::json_parser_error e)
    {
        Logger_->Critical(fileName + "�̓ǂݍ��݂Ɏ��s���܂����B\n�ڍ�: " + e.what());
        if(autoCreate)
        {
            Logger_->Warn("�t�@�C����������Ȃ��̂ō쐬���܂�...");
            std::ofstream f(fileName);
            f.write("{}", 2);
            f.close();

            if (Load(fileName, false))
            {
                //SettingsTree_.push_back(std::make_pair("", DefaultTree_));
                Save();
                Logger_->Warn("�t�@�C�����쐬���܂����B");
                return true;
            }
        }
    }

    return false;
}

bool SettingManager::Load(bool autoCreate)
{
    return Load(FileName_, autoCreate);
}

bool SettingManager::Reload()
{
    Logger_->Debug(FileName_ + " �ēǍ�");
    return Load(FileName_);
}

bool SettingManager::Save()
{
    return Save(FileName_);
}

bool SettingManager::Save(const std::string &fileName)
{
    Logger_->Info(fileName + "�ۑ���...");

    try {
        write_json(fileName, SettingsTree_);
        Logger_->Info(FileName_ + " �ۑ�");
        return true;
    } catch(boost::property_tree::json_parser::json_parser_error e)
    {
        Logger_->Critical(fileName + "�̕ۑ��Ɏ��s���܂����B\n�ڍ�: " + e.what());
    }
    return false;
}

void SettingManager::Close()
{
    FileName_ = "";
}

void SettingManager::SetGlobal()
{
    if(!GlobalSettings_)
    {
        GlobalSettings_ = this;
        Logger_->Warn("�O���[�o���ݒ�ɂȂ�܂����B");
    }else
    {
        Logger_->Error("���ɃO���[�o���ݒ肪���݂���̂�SetGlobal()���Ă΂�܂���");
    }
}

SettingManager* SettingManager::GetGlobal()
{
    return GlobalSettings_;
}

/*template <class T> void SettingManager::SetDefault(const std::string &dataPath, T value)
{
    DefaultTree_.put(dataPath, value);
}

template<class T> T SettingManager::Get(const std::string &dataPath)
{
    if (boost::optional<T> value = SettingsTree_.get_optional<T>(dataPath))
    {
        return value.get();
    }
    return nullptr;
}

template <class T> void SettingManager::Set(const std::string &dataPath, T value)
{
    SettingsTree_.put(dataPath, value);
}
*/
