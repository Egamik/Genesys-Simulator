/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SourceModelCOmponent.cpp
 * Author: cancian
 * 
 * Created on 21 de Junho de 2018, 19:50
 */

#include "SourceModelComponent.h"

SourceModelComponent::SourceModelComponent(Model* model):ModelComponent(model) {
}

SourceModelComponent::SourceModelComponent(const SourceModelComponent& orig):ModelComponent(orig) {
}

SourceModelComponent::~SourceModelComponent() {
}

void SourceModelComponent::setFirstCreation(double _firstCreation) {
	this->_firstCreation = _firstCreation;
}

double SourceModelComponent::getFirstCreation() const {
	return _firstCreation;
}

void SourceModelComponent::setCollectStatistics(bool _collectStatistics) {
	this->_collectStatistics = _collectStatistics;
}

bool SourceModelComponent::isCollectStatistics() const {
	return _collectStatistics;
}

void SourceModelComponent::setEntityType(std::string _entityType) {
	this->_entityType = _entityType;
}

std::string SourceModelComponent::getEntityType() const {
	return _entityType;
}

void SourceModelComponent::setTimeUnit(Util::TimeUnit _timeUnit) {
	this->_timeUnit = _timeUnit;
}

Util::TimeUnit SourceModelComponent::getTimeUnit() const {
	return _timeUnit;
}

void SourceModelComponent::setTimeBetweenCreationsExpression(std::string _timeBetweenCreations) {
	this->_timeBetweenCreationsExpression = _timeBetweenCreations;
}

std::string SourceModelComponent::getTimeBetweenCreationsExpression() const {
	return _timeBetweenCreationsExpression;
}

void SourceModelComponent::setMaxCreations(unsigned int _maxCreations) {
	this->_maxCreations = _maxCreations;
}

unsigned int SourceModelComponent::getMaxCreations() const {
	return _maxCreations;
}

