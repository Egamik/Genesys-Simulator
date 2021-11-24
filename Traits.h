/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Traits.h
 * Author: rafael.luiz.cancian
 *
 * Created on 14 de Agosto de 2018, 19:36
 */

#ifndef TRAITS_H
#define TRAITS_H

#include "kernel/util/Util.h"
#include "userInterfaces/terminal/GenesysTerminalApp.h"
#include "userInterfaces/gui/qt/GenesysQtGUI.h"
#include "userInterfaces/examples/Example_SeizeDelayRelease1.h"
#include "userInterfaces/examples/book/Example01.h"
//#include "userInterfaces/examples/Example_SistemaOperacional03.h"

#include "tools/IntegratorDefaultImpl1.h"

template <typename T>
struct Traits {
};

/*
 *  Genesys Application
 */

template <> struct Traits<GenesysApplication_if> {
    static const Util::TraceLevel traceLevel = Util::TraceLevel::L6_arrival;
    typedef Example01 Application;

};

template <> struct Traits<Integrator_if> {
    typedef IntegratorDefaultImpl1 Implementation;
    static constexpr double MaxSteps = 1e3;
};

#endif /* TRAITS_H */

