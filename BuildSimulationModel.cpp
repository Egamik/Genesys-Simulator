/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

using namespace std;


#include "BuildSimulationModel.h"

// GEnSyS Simulator
#include "Simulator.h"

// Configuration
#include "Traits.h"


// Model Components
#include "Create.h"
#include "Delay.h"
#include "Dispose.h"
#include "Seize.h"
#include "Release.h"
#include "Assign.h"
#include "ModelSimulation.h"

void traceHandler(TraceEvent e) {
	std::cout << e.getText() << std::endl;
}

void traceSimulationHandler(TraceSimulationEvent e) {
	std::cout << e.getText() << std::endl;
}

void onReplicationStartHandler(SimulationEvent* re) {
	std::cout << "Replication " << re->getReplicationNumber() << " starting.";
}

void onProcessEventHandler(SimulationEvent* re) {
	std::cout << "Processing event " << re->getEventProcessed()->show();
}

void onReplicationEndHandler(SimulationEvent* re) {
	std::cout << "Replication " << re->getReplicationNumber() << " ending.";
}

void buildModel(Model* model) { // buildModelWithAllImplementedComponents
	// traces handle and simulation events to output them
	TraceManager* tm = model->getTracer(); 
	tm->addTraceListener(&traceHandler);
	tm->addTraceReportListener(&traceHandler);
	tm->addTraceSimulationListener(&traceSimulationHandler);

	OnEventManager* ev = model->getOnEventManager();
	ev->addOnReplicationStartListener(&onReplicationStartHandler);
	ev->addOnReplicationEndListener(&onReplicationEndHandler);
	ev->addOnProcessEventListener(&onProcessEventHandler);

	ModelInfo* infos = model->getInfos();
	infos->setAnalystName("Meu nome");
	infos->setDescription("Esse é um modelo de teste dos componentes já implementados");
	infos->setNumberOfReplications(1);
	infos->setReplicationLength(1);
	infos->setReplicationLengthTimeUnit(Util::TimeUnit::hour);
	
	// create and insert model components to the model
	Create* create1 = new Create(model);
	create1->setTimeBetweenCreationsExpression("1.5");
	create1->setTimeUnit(Util::TimeUnit::minute);
	create1->setEntitiesPerCreation(2);
	
	Assign* assign1 = new Assign(model);
	Assign::Assignment* attrib1Assignment = new Assign::Assignment(Assign::DestinationType::Attribute, "Attribute 1", "Variable 1");
	assign1->getAssignments()->insert(attrib1Assignment);
	Assign::Assignment* attrib2Assignment = new Assign::Assignment(Assign::DestinationType::Variable, "Variable 1", "Variable 1 + 1");
	assign1->getAssignments()->insert(attrib2Assignment);

	Seize* seize1 = new Seize(model);
	seize1->setResourceName("Máquina 1");

	Delay* delay1 = new Delay(model);
	delay1->setDelayExpression("30");

	Release* release1 = new Release(model);
	release1->setResourceName("Máquina 1");
	release1->setQueueName(seize1->getQueueName());

	Dispose* dispose1 = new Dispose(model);

	// add the components to the model
	List<ModelComponent*>* components = model->getComponents();
	components->insert(create1);
	components->insert(assign1);
	components->insert(seize1);
	components->insert(delay1);
	components->insert(release1);
	components->insert(dispose1);

	// connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
	create1->getNextComponents()->insert(assign1);
	assign1->getNextComponents()->insert(seize1);
	seize1->getNextComponents()->insert(delay1);
	delay1->getNextComponents()->insert(release1);
	release1->getNextComponents()->insert(dispose1);
}

BuildSimulationModel::BuildSimulationModel() {

}

void buildSimulationSystem() {
	Simulator* simulator = new Simulator();
	Model* model = new Model(simulator);
	buildModel(model);
	simulator->getModels()->insert(model);
	
	SimulationControl* control = model->getControls()->first();
	std::string name = control->getName();
	double value = control->getValue();
	control->setValue(3);
	value = control->getValue();
	
	if (model->checkModel()) {
		model->saveModel("./genesysmodel.txt");
		model->getSimulation()->startSimulation();
	}
}

int BuildSimulationModel::main(int argc, char** argv) {
	buildSimulationSystem();
};