//-----------------------------------------------------------------------------
// Subsystem:   Ntuples
// Package:     substructure
// Description: TheNtupleMaker helper class for pat::Jet
// Created:     Tue May  8 17:05:51 2012
// Author:      Sezen Sekmen      
//-----------------------------------------------------------------------------
#include "PhysicsTools/TheNtupleMaker/interface/patJetHelper.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/ParticleFlowReco/interface/PFBlockFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h"

#include <fastjet/PseudoJet.hh>
#include "Njettiness.hh"
#include "EnergyCorrelator.hh"

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "ShapeWithComponents.hh"
#include "GenericSubtractor.hh"

//-----------------------------------------------------------------------------
using namespace std;
using namespace pat;
//-----------------------------------------------------------------------------

using namespace fastjet;



class NSubjettinessRatio : public contrib::ShapeWithComponents{
public:
  NSubjettinessRatio(int N) : _N(N){
    assert(_N>1);
  }

  // a (rather loosy) description
  virtual std::string description() const{ return "N-subjettiness ratio from components";}

  /// returns the number of components 
  virtual unsigned int n_components() const { return 2;}

  /// computes individually tau_N and tau_{N-1}
  virtual std::vector<double> components(const PseudoJet &jet) const{
    vector<double> comp(n_components());
    NsubParameters paraNsub = NsubParameters(1.0, 0.8); //assume R=0.8 jet clusering used
    Njettiness routine(Njettiness::onepass_kt_axes, paraNsub);
    comp[0] = routine.getTau(_N, jet.constituents()); 
    comp[1] = routine.getTau(_N-1, jet.constituents()); 
    return comp;
  }

  /// given the components, determine the result of the event shape
  virtual double result_from_components(const std::vector <double> &components) const{
    return components[0]/components[1];
  }

protected:
  const int _N;
};


// This constructor is called once per job
JetHelper::JetHelper()
  : HelperFor<pat::Jet>() {}
    
JetHelper::~JetHelper() {}

// -- Called once per event
void JetHelper::analyzeEvent()
{
  event->getByLabel(labelname, jets_);
  event->getByLabel("genParticlesForJetsNoNu", genParticles_);
  //event->getByLabel(labelname+"puJetId", puJetId_);
  //event->getByLabel("ak5PFJetsCHSprunedSubJetspuJetId", subJetpuJetId_);
}

// -- Called once per object
void JetHelper::analyzeObject()
{
  // write only jets with pt > 15:

  if (!(object->pt() > 30)) {
    count = 0;
  }
}

float JetHelper::getPt(unsigned int num) const
{
    if(object->getPFConstituents().size()>num)
    {
        const reco::PFCandidate *thisParticle = object->getPFConstituent(num).get();
        return thisParticle->pt();
    }
    return 0;
}

float JetHelper::getChargedPt(unsigned int num) const
{
    unsigned int counter=-1;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
        const reco::PFCandidate *thisParticle = object->getPFConstituent(k).get();
        if(thisParticle->charge()!=0)
	    counter++;
	if(num==counter)
            return thisParticle->pt();
    }
    return 0;
}

int JetHelper::getNcharged(double relPt) const
{
    int n=0;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
        const reco::PFCandidate *thisParticle = object->getPFConstituent(k).get();
        if((thisParticle->charge()!=0)&&(thisParticle->pt()>relPt*object->pt()))
            n++;
    }
    return n; 
}

int JetHelper::getNneutral(double relPt) const
{
    int n=0;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
        const reco::PFCandidate *thisParticle = object->getPFConstituent(k).get();
        if((thisParticle->charge()==0)&&(thisParticle->pt()>relPt*object->pt()))
            n++;
    }
    return n; 
}

int JetHelper::genNCHS() const
{
    int n=0;
    double vertexZ=-1000;
    vector<const reco::GenParticle*> all_particles;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(vertexZ==-1000)
           vertexZ=p->vz();
       if((abs(p->vz()-vertexZ)<0.1)||(p->charge()==0))
            n++;
    }
    return n; 
}

float JetHelper::getTau(int num) const
{
    vector<fastjet::PseudoJet> FJparticles;
    if(object->isPFJet())
    {
       for (unsigned k =0; k < object->getPFConstituents().size(); k++)
          FJparticles.push_back( fastjet::PseudoJet( object->getPFConstituent(k)->px(), object->getPFConstituent(k)->py(), object->getPFConstituent(k)->pz(), object->getPFConstituent(k)->energy() ));
    } else {
       for (unsigned j = 0; j < object->numberOfDaughters(); j++){
          reco::Jet const *pfSubjet = dynamic_cast <const reco::Jet *>(object->daughter(j));
          if (!pfSubjet) break;
          for (unsigned k =0; k < pfSubjet->numberOfDaughters(); k++)
              FJparticles.push_back( fastjet::PseudoJet( pfSubjet->daughter(k)->px(), pfSubjet->daughter(k)->py(), pfSubjet->daughter(k)->pz(), pfSubjet->daughter(k)->energy() ));
       }
    }
    NsubParameters paraNsub = NsubParameters(1.0, 0.8); //assume R=0.8 jet clusering used
    Njettiness routine(Njettiness::onepass_kt_axes, paraNsub);
    return routine.getTau(num, FJparticles); 
}

float JetHelper::getGenTau(int num, double minPt, bool CHS) const
{
    double vertexZ=-1000;
    vector<fastjet::PseudoJet> FJparticles;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(p) {
         if(vertexZ==-1000)
             vertexZ=p->vz();
         if((abs(p->vz()-vertexZ)<0.1)||(p->charge()==0)||(!CHS))
	  if(p->pt()>minPt)
            FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ));
       } else {
         reco::GenJet const *pfSubjet = dynamic_cast <const reco::GenJet *>(object->daughter(j));
         if (!pfSubjet) break;
         for (unsigned k =0; k < pfSubjet->numberOfDaughters(); k++)
	 {
          reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(pfSubjet->daughter(k));
	  if(p->pt()>minPt)
            FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ));
	 }
       }
    }
    NsubParameters paraNsub = NsubParameters(1.0, 0.8); //assume R=0.8 jet clusering used
    Njettiness routine(Njettiness::onepass_kt_axes, paraNsub);
    return routine.getTau(num, FJparticles); 
}

float JetHelper::getGenCaloJetMass(double calosize, bool PF, bool correctTracks) const
{
    vector<fastjet::PseudoJet> FJparticles;
    map<int,unsigned> calomap;
    map<int,vector<unsigned> > trackmap;
    //std::cerr << "find calo cells and tracks" << std::endl;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(p) {
         int index=int(p->y()/calosize)+1000*int(p->phi()/calosize);
         if((p->charge()==0)||(!PF))
	 {
	   if(calomap.count(index)>0)
	   {
	    FJparticles[calomap[index]]+=fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() );
           } else {
	    calomap[index]=FJparticles.size();
	    FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
	   }
	 } else {
          trackmap[index].push_back(FJparticles.size());
          FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
	 }
       }
    }
    //std::cerr << "make towers" << std::endl;
    for (map<int,unsigned>::iterator iter=calomap.begin(); iter!=calomap.end(); ++iter){
        FJparticles[iter->second]= fastjet::PtYPhiM(FJparticles[iter->second].pt(),(int(FJparticles[iter->second].rapidity()/calosize)+0.5)*calosize,(int(FJparticles[iter->second].phi()/calosize)+0.5)*calosize,FJparticles[iter->second].m());
    }
    //std::cerr << "correct with tracks" << std::endl;
    if ((PF)&&(correctTracks)) {
    for (map<int,unsigned>::iterator iter=calomap.begin(); iter!=calomap.end(); ++iter){
      double pTsum=0;
      for (vector<unsigned>::iterator iter2=trackmap[iter->first].begin(); iter2!=trackmap[iter->first].end(); ++iter2)
        pTsum+=FJparticles[*iter2].pt();
      if(pTsum==0) continue;
      double factor=FJparticles[iter->second].pt()/pTsum;
      fastjet::PseudoJet corrected;
      for (vector<unsigned>::iterator iter2=trackmap[iter->first].begin(); iter2!=trackmap[iter->first].end(); ++iter2){
	  corrected+=fastjet::PseudoJet( FJparticles[*iter2].px()*factor, FJparticles[*iter2].py()*factor, FJparticles[*iter2].pz()*factor, FJparticles[*iter2].E()*factor );
      }
      FJparticles[iter->second]=corrected;
    }
    }
    //std::cerr << "rerun clustering" << std::endl;
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0));
    fastjet::Pruner pruner(fastjet::cambridge_algorithm, 0.1, 0.5);
    double mass=-1;
    if(inclusive_jets.size()>0)
         mass=pruner(inclusive_jets[0]).m();
    //std::cerr << "done" << std::endl;
    return mass;
}

float JetHelper::getGenTrackJetMass() const
{
    vector<fastjet::PseudoJet> FJparticles;
    //std::cerr << "find tracks" << std::endl;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(p) {
         if((p->charge()!=0))
          FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
       }
    }
    //std::cerr << "rerun clustering for tracks" << std::endl;
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0));
    fastjet::Pruner pruner(fastjet::cambridge_algorithm, 0.1, 0.5);
    double mass=-1;
    if(inclusive_jets.size()>0)
         mass=pruner(inclusive_jets[0]).m();
    //std::cerr << "done" << std::endl;
    return mass;
}

float JetHelper::getPrunedJetMass() const
{
    vector<fastjet::PseudoJet> FJparticles;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
       const reco::PFCandidate *p = object->getPFConstituent(k).get();
       if(!p) continue;
       FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
    }
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0));
    if(inclusive_jets.size()==0) return 0;
    double jetCorrection=object->pt()/inclusive_jets[0].pt();
    fastjet::Pruner pruner(fastjet::cambridge_algorithm, 0.1, 0.5);
    return pruner(inclusive_jets[0]).m()*jetCorrection;
}

float JetHelper::getTrackJetMass() const
{
    vector<fastjet::PseudoJet> FJparticles;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
       const reco::PFCandidate *p = object->getPFConstituent(k).get();
       if(!p) continue;
       if(p->charge()!=0) //charge particles
         FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
    }
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0));
    if(inclusive_jets.size()==0) return 0;
    double jetCorrection=object->pt()/inclusive_jets[0].pt();
    fastjet::Pruner pruner(fastjet::cambridge_algorithm, 0.1, 0.5);
    return pruner(inclusive_jets[0]).m()*jetCorrection;
}

// shortened from #include "RecoParticleFlow/PFClusterProducer/interface/PFClusterAlgo.h"
void resetClusterPosition(reco::PFCluster& cluster) {

  std::vector< std::pair< DetId, float > > hits_and_fracts;

  cluster.setPosition(math::XYZPoint(0,0,0));

  double normalize = 0;

  // calculate average layer  ---------- //

  // double layer = 0;
  map <PFLayer::Layer, double> layers; 

  // loop over pairs to find layer with max energy          
  double Emax = 0.;
  PFLayer::Layer layer = PFLayer::NONE;
  for (map<PFLayer::Layer, double>::iterator it = layers.begin();
       it != layers.end(); ++it) {
    double e = it->second;
    if(e > Emax){ 
      Emax = e; 
      layer = it->first;
    }
  }

  //setlayer here
  cluster.setLayer( layer ); // take layer with max energy

  double p1 =  0.08;

  // calculate uncorrected cluster position --------------------------------

  math::XYZPoint clusterposxyz;           // idem, xyz coord 
  math::XYZPoint firstrechitposxyz;       // pos of the rechit with highest E

  double maxe = -9999;
  double x = 0;
  double y = 0;
  double z = 0;
  
  for (unsigned ic=0; ic<cluster.recHitFractions().size(); ic++ ) {
    
    const reco::PFRecHit& rh = *(cluster.recHitFractions()[ic].recHitRef());

    hits_and_fracts.push_back(std::make_pair(DetId(rh.detId()),
				     cluster.recHitFractions()[ic].fraction()));

    double fraction = hits_and_fracts.back().second;
    double recHitEnergy = rh.energy() * fraction;
    double norm = fraction < 1E-9 ? 0. : max(0., log(recHitEnergy/p1));
        
    const math::XYZPoint& rechitposxyz = rh.position();
    
    if( recHitEnergy > maxe ) {
      firstrechitposxyz = rechitposxyz;
      maxe = recHitEnergy;
    }

    x += rechitposxyz.X() * norm;
    y += rechitposxyz.Y() * norm;
    z += rechitposxyz.Z() * norm;
    
    normalize += norm;
  }

  // normalize uncorrected position

  if( normalize < 1e-9 ) {
    //    cerr<<"--------------------"<<endl;
    //    cerr<<(*this)<<endl;
    cout << "Watch out : cluster too far from its seeding cell, set to 0,0,0" << endl;
    clusterposxyz.SetCoordinates(0,0,0);
    return;
  }
  else {
    x /= normalize;
    y /= normalize; 
    z /= normalize; 

    clusterposxyz.SetCoordinates( x, y, z);

  }  

  cluster.setPosition(clusterposxyz);
  cluster.calculatePositionREP();

}


// RECALCULATE CLUSTER POSITIONS
float JetHelper::getCorrectedPrunedJetMass() const
{
    vector<fastjet::PseudoJet> FJparticles;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
       const reco::PFCandidate *p = object->getPFConstituent(k).get();
       if(!p) continue;
       FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
       for (unsigned j =0; j < p->elementsInBlocks().size(); j++)
       {
	   const reco::PFBlockElement* element = & p->elementsInBlocks()[j].first->elements()[p->elementsInBlocks()[j].second];
	   if((element->type()==4)) //ECAL clusters
	   {
	     reco::PFCluster cluster = *element->clusterRef();
	     double clusterPt = cluster.pt()*p->ecalEnergy()/p->rawEcalEnergy();
	     if((clusterPt<1e-2)||(clusterPt>1e10)||(p->rawEcalEnergy()<1e-2)) continue;
	     //std::cerr << element->type() << ":" << clusterPt;
	     fastjet::PseudoJet originalClusterVector = fastjet::PtYPhiM( clusterPt, cluster.eta(), cluster.phi(), 0 );
	     resetClusterPosition(cluster);
	     fastjet::PseudoJet recalibratedClusterVector = fastjet::PtYPhiM( clusterPt, cluster.eta(), cluster.phi(), 0 );
	     //std::cerr << "," << originalClusterVector.eta() << "->" << recalibratedClusterVector.eta() << "," << originalClusterVector.phi() << "->" << recalibratedClusterVector.phi() << std::endl;
             FJparticles[k]-=originalClusterVector;
             FJparticles[k]+=recalibratedClusterVector;
           }
	   if((element->type()==5)) //HCAL clusters
	   {
	     reco::PFCluster cluster = *element->clusterRef();
	     double clusterPt = cluster.pt()*p->hcalEnergy()/p->rawHcalEnergy();
	     if((clusterPt<1e-2)||(clusterPt>1e10)||(p->rawHcalEnergy()<1e-2)) continue;
	     //std::cerr << element->type() << ":" << clusterPt;
	     fastjet::PseudoJet originalClusterVector = fastjet::PtYPhiM( clusterPt, cluster.eta(), cluster.phi(), 0 );
	     resetClusterPosition(cluster);
	     fastjet::PseudoJet recalibratedClusterVector = fastjet::PtYPhiM( clusterPt, cluster.eta(), cluster.phi(), 0 );
	     //std::cerr << "," << originalClusterVector.eta() << "->" << recalibratedClusterVector.eta() << "," << originalClusterVector.phi() << "->" << recalibratedClusterVector.phi() << std::endl;
             FJparticles[k]-=originalClusterVector;
             FJparticles[k]+=recalibratedClusterVector;
           }
       }
       //if((FJparticles[k].E()<0)||(FJparticles[k].m2()<0)||(FJparticles[k].E()>1e10)||(FJparticles[k].m2()>1e10)||(FJparticles[k].eta()>10))
          //FJparticles[k]*=0;
    }
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0));
    if(inclusive_jets.size()==0) return 0;
    double jetCorrection=object->pt()/inclusive_jets[0].pt();
    fastjet::Pruner pruner(fastjet::cambridge_algorithm, 0.1, 0.5);
    return pruner(inclusive_jets[0]).m()*jetCorrection;
}

float JetHelper::getSplitBlockPrunedJetMass() const
{
    vector<fastjet::PseudoJet> FJparticles;
    map<unsigned,vector<fastjet::PseudoJet> > clusters;
    for (unsigned k =0; k < object->getPFConstituents().size(); k++)
    {
       const reco::PFCandidate *p = object->getPFConstituent(k).get();
       if(!p) continue;
       FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ) );
       for (unsigned j =0; j < p->elementsInBlocks().size(); j++)
       {
         if(p->pdgId()==130) //neutral hadrons
	 {
	   const reco::PFBlockElement* element = & p->elementsInBlocks()[j].first->elements()[p->elementsInBlocks()[j].second];
	   if(element->type()==4) //ECAL clusters
             clusters[k].push_back( fastjet::PtYPhiM( element->clusterRef()->pt()*(p->ecalEnergy()+p->hcalEnergy())/p->rawEcalEnergy(), element->clusterRef()->eta(), element->clusterRef()->phi(), 0 ) );
	 }
       }
    }
    for (map<unsigned,vector<fastjet::PseudoJet> >::iterator iter=clusters.begin(); iter!=clusters.end(); ++iter){
      double pTsum=0;
      //std::cout << FJparticles[iter->first].pt() << " = ";
      for (vector<fastjet::PseudoJet>::iterator iter2=iter->second.begin(); iter2!=iter->second.end(); ++iter2) {
        pTsum+=iter2->pt();
        //std::cout << iter2->pt() << "+";
      }
      //std::cout << std::endl;
      if(pTsum==0) continue;
      double factor=FJparticles[iter->first].pt()/pTsum;
      fastjet::PseudoJet corrected;
      for (vector<fastjet::PseudoJet>::iterator iter2=iter->second.begin(); iter2!=iter->second.end(); ++iter2) {
	  corrected += fastjet::PseudoJet( iter2->px()*factor, iter2->py()*factor, iter2->pz()*factor, iter2->E()*factor );
      }
      FJparticles[iter->first]=corrected;
    }
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0));
    if(inclusive_jets.size()==0) return 0;
    double jetCorrection=object->pt()/inclusive_jets[0].pt();
    fastjet::Pruner pruner(fastjet::cambridge_algorithm, 0.1, 0.5);
    return pruner(inclusive_jets[0]).m()*jetCorrection;
}

float JetHelper::genTau21PUcorrected(double minPt, bool CHS) const
{
    double vertexZ=-1000;
    vector<fastjet::PseudoJet> FJparticles;
    vector<fastjet::PseudoJet> HARDparticles;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(vertexZ==-1000)
           vertexZ=p->vz();
       if((abs(p->vz()-vertexZ)<0.1)||(p->charge()==0)||(!CHS))
	if(p->pt()>minPt)
          FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ));
       if((abs(p->vz()-vertexZ)<0.1))
	if(p->pt()>minPt)
          HARDparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ));
    }

    // background estimation
    vector<fastjet::PseudoJet> Allparticles;
    for (unsigned i = 0; i < genParticles_->size(); i++){
        reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(&(*genParticles_)[i]);
        if((abs(p->vz()-vertexZ)<0.1)||(p->charge()==0)||(!CHS))
           if(p->pt()>minPt)
               Allparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ));
    }
    JetDefinition jet_def_for_rho(kt_algorithm, 0.6);
    AreaDefinition area_def(active_area_explicit_ghosts,
    		      GhostedAreaSpec(SelectorAbsRapMax(5.0)));
    Selector rho_range =  SelectorAbsRapMax(4.4);
    JetMedianBackgroundEstimator bge(rho_range, jet_def_for_rho, area_def);
    bge.set_particles(Allparticles);
    
    // background stubstraction
    Subtractor subtractor(&bge);
    contrib::GenericSubtractor gen_sub(&bge);
    //gen_sub.use_common_bge_for_rho_and_rhom();
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequenceArea clust_seq(FJparticles, jet_def, area_def);
    vector<fastjet::PseudoJet> inclusive_jets = clust_seq.inclusive_jets(0);
    NSubjettinessRatio tau21(2);
    
    // validation
    //std::cerr << "rho" << bge.rho() << std::endl;
    //fastjet::ClusterSequenceArea clust_seq_hard(HARDparticles, jet_def, area_def);
    //vector<fastjet::PseudoJet> hard_jets = clust_seq_hard.inclusive_jets(0);
    //std::cerr << "hard" << (hard_jets[hard_jets.size()-1].pt()) << " orig" << (inclusive_jets[inclusive_jets.size()-1].pt()) << " corrected" << (subtractor(inclusive_jets[inclusive_jets.size()-1]).pt()) << std::endl;
    //std::cerr << "orig" << tau21(inclusive_jets[inclusive_jets.size()-1]) << " corrected" << gen_sub(tau21, inclusive_jets[inclusive_jets.size()-1]) << std::endl;

    return gen_sub(tau21, inclusive_jets[inclusive_jets.size()-1]);
}


float JetHelper::getC2beta(float beta) const
{
    vector<fastjet::PseudoJet> FJparticles;
    if(object->isPFJet())
    {
       for (unsigned k =0; k < object->getPFConstituents().size(); k++)
          FJparticles.push_back( fastjet::PseudoJet( object->getPFConstituent(k)->px(), object->getPFConstituent(k)->py(), object->getPFConstituent(k)->pz(), object->getPFConstituent(k)->energy() ));
    } else {
       for (unsigned j = 0; j < object->numberOfDaughters(); j++){
          reco::Jet const *pfSubjet = dynamic_cast <const reco::Jet *>(object->daughter(j));
          if (!pfSubjet) break;
          for (unsigned k =0; k < pfSubjet->numberOfDaughters(); k++)
              FJparticles.push_back( fastjet::PseudoJet( pfSubjet->daughter(k)->px(), pfSubjet->daughter(k)->py(), pfSubjet->daughter(k)->pz(), pfSubjet->daughter(k)->energy() ));
       }
    }
    if(FJparticles.size()<2) return -1;
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = clust_seq.inclusive_jets(0);
    contrib::EnergyCorrelatorRatio C2beta(2,beta,contrib::EnergyCorrelator::pt_R);
    return C2beta(inclusive_jets[0]);
}

float JetHelper::getGenC2beta(float beta, bool CHS) const
{
    double vertexZ=-1000;
    vector<fastjet::PseudoJet> FJparticles;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(vertexZ==-1000)
           vertexZ=p->vz();
       if((abs(p->vz()-vertexZ)<0.1)||(p->charge()==0)||(!CHS))
           FJparticles.push_back( fastjet::PseudoJet( p->px(), p->py(), p->pz(), p->energy() ));
    }
    if(FJparticles.size()<2) return -1;
    fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm, 2.0);
    fastjet::ClusterSequence clust_seq(FJparticles, jet_def);
    vector<fastjet::PseudoJet> inclusive_jets = clust_seq.inclusive_jets(0);
    contrib::EnergyCorrelatorRatio C2beta(2,beta,contrib::EnergyCorrelator::pt_R);
    return C2beta(inclusive_jets[0]);
}

float JetHelper::getJetCharge(float kappa) const
{
    float val=0;
    if(object->isPFJet())
    {
       for (unsigned k =0; k < object->getPFConstituents().size(); k++)
       {
          const reco::PFCandidate* p=object->getPFConstituent(k).get();
          val += p->charge()*pow(p->pt(),kappa);
       }
    } else {
       for (unsigned j = 0; j < object->numberOfDaughters(); j++){
          reco::Jet const *pfSubjet = dynamic_cast <const reco::Jet *>(object->daughter(j));
          if (!pfSubjet) break;
          for (unsigned k =0; k < pfSubjet->numberOfDaughters(); k++)
	  {
             const reco::Candidate* p=pfSubjet->daughter(k);
             val += p->charge()*pow(p->pt(),kappa);
	  }
       }
    }
    return val/pow(object->pt(),kappa); 
}


float JetHelper::getGenJetCharge(float kappa, bool CHS) const
{
    double vertexZ=-1000;
    float val=0;
    vector<const reco::GenParticle*> all_particles;
    for (unsigned j = 0; j < object->numberOfDaughters(); j++){
       reco::GenParticle const *p = dynamic_cast <const reco::GenParticle *>(object->daughter(j));
       if(vertexZ==-1000)
           vertexZ=p->vz();
       if((abs(p->vz()-vertexZ)<0.1)||(p->charge()==0)||(!CHS))
           val += p->charge()*pow(p->pt(),kappa);
    }
    return val/pow(object->pt(),kappa); 
}


float JetHelper::getDaughter_0_jetCharge(float kappa) const
{
    float val=0;
    if(object->numberOfDaughters()>0)
    {
       reco::Jet const *pfSubjet = dynamic_cast <const reco::Jet *>(object->daughter(0));
       if (pfSubjet){
       for (unsigned k =0; k < pfSubjet->numberOfDaughters(); k++)
       {
    	  const reco::Candidate* p=pfSubjet->daughter(k);
    	  val += p->charge()*pow(p->pt(),kappa);
       }
       val/=pow(pfSubjet->pt(),kappa);
       }
    }
    return val; 
}

float JetHelper::getDaughter_1_jetCharge(float kappa) const
{
    float val=0;
    if(object->numberOfDaughters()>1)
    {
       reco::Jet const *pfSubjet = dynamic_cast <const reco::Jet *>(object->daughter(1));
       if (pfSubjet){
       for (unsigned k =0; k < pfSubjet->numberOfDaughters(); k++)
       {
    	  const reco::Candidate* p=pfSubjet->daughter(k);
    	  val += p->charge()*pow(p->pt(),kappa);
       }
       val/=pow(pfSubjet->pt(),kappa);
       }
    }
    return val; 
}
