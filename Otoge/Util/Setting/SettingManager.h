#pragma once

#include "../Debug/Logger.h"

class SettingManager
{
private:
    std::shared_ptr<Logger> Logger_;
    std::string FileName_;
    boost::property_tree::ptree SettingsTree_;
    boost::property_tree::ptree DefaultTree_;

    static SettingManager *GlobalSettings_;

    bool CanProcess();

public:
    SettingManager(const std::string &fileName);
    ~SettingManager();

    bool Load(const std::string &fileName, bool autoCreate = false);
    bool Load(bool autoCreate = false);
    bool Reload();
    bool Save();
    bool Save(const std::string &fileName);
    void Close();
    void SetGlobal();
    static SettingManager *GetGlobal();


    template<typename T> void SetDefault(const std::string &dataPath, T value)
    {
        Logger_->Debug("�����l�Z�b�g: " + dataPath + " = " + std::to_string(value));

        if(SettingsTree_.get_optional<T>(dataPath) == boost::none)
        {
            Logger_->Info("������: " + dataPath);
            Set(dataPath, value);
        }
        
        //DefaultTree_.put(dataPath, value);
    }

    template<typename T> boost::optional<T> Get(const std::string &dataPath)
    {
        if (boost::optional<T> value = SettingsTree_.get_optional<T>(dataPath))
        {
            Logger_->Debug( "�擾����: " + dataPath + " = " + std::to_string(value.get()));
            return value;
        }else
        {
            Logger_->Error("�擾���s: " + dataPath);
            return boost::none;
        }
    }

    template<typename T> void Set(const std::string &dataPath, T value)
    {
        SettingsTree_.put(dataPath, value);
    }
};
