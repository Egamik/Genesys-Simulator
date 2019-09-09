/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Station.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:12
 */

#ifndef STATION_H
#define STATION_H

#include "ModelElement.h"
#include "ElementManager.h"
#include "Plugin.h"

class Station: public ModelElement {
public:
    Station(ElementManager* elems);
    Station(ElementManager* elems, std::string name);
    Station(const Station& orig);
    virtual ~Station();
public:
    virtual std::string show();
public: // static 
    static PluginInformation* GetPluginInformation();
    static ModelElement* LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields);
public:
    void initBetweenReplications();
protected:
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    virtual bool _check(std::string* errorMessage);
private:
    void _initCStats();
private:
    ElementManager* _elems;
};

#endif /* STATION_H */

