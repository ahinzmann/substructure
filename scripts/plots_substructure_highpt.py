import os, sys
import array
from ROOT import * 
from os import path

#gROOT.Reset()
#gROOT.SetStyle("Plain")
gROOT.ProcessLine('.L tdrstyle.C')
gStyle.SetOptStat(0)
gStyle.SetOptFit(0)
gStyle.SetTitleOffset(1.3,"Y")
gStyle.SetPadLeftMargin(0.15)
gStyle.SetPadBottomMargin(0.15)
gStyle.SetPadTopMargin(0.08)
gStyle.SetPadRightMargin(0.08)
gStyle.SetMarkerSize(0.5)
gStyle.SetHistLineWidth(1)
#gStyle.SetStatFontSize(0.020	
gStyle.SetTitleSize(0.06, "XYZ")
gStyle.SetLabelSize(0.05, "XYZ")
gStyle.SetNdivisions(506, "XYZ")
gStyle.SetLegendBorderSize(0)

TGaxis.SetMaxDigits(3)

if __name__ == '__main__':

 for filename in ["WW3000","QCD30","QCD170","QCD1000"]:
  for resolution in [False,True]:
   for runSet in [32,33]:
     
     if runSet==32:
      samples = ["substructure_pas_"+filename+"_fixTRACK.root",
 		 #"substructure_pas_"+filename+".root",
 		 "substructure_pas_"+filename+"_posHCAL.root",
 		 #"substructure_pas_"+filename+"_posCAL.root",
 		 #"substructure_pas_"+filename+"_fixHCAL.root",
 		 "substructure_pas_"+filename+"_fixTRACK_noHCAL.root",
 		 ]
      names = ["pt",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
 	       ]
      colors=[4,2,1,6,2,2,6,6,6]
      styles=[2,1,3,2,1,3,2,1,3]
      widths=[2,1,1,2,1,1,2,1,1]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==33:
      if filename!="WW3000": continue
      samples = ["substructure_pas_"+filename+"_fixTRACK.root",
 		 #"substructure_pas_"+filename+".root",
 		 "substructure_pas_"+filename+"_posHCAL.root",
 		 #"substructure_pas_"+filename+"_posCAL.root",
 		 #"substructure_pas_"+filename+"_fixHCAL.root",
 		 "substructure_pas_"+filename+"_fixTRACK_noHCAL.root",
 		 ]
      names = ["pt",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4)&&(deta<1.3)&&(DijetMass>2000)&&(Jet1pt>1100)&&(Jet1pt<1700))","jet p_{T} (GeV)"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4)&&(deta<1.3)&&(DijetMass>2000)&&(Jet1pt>1100)&&(Jet1pt<1700))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(deta<1.3)&&(DijetMass>2000)&&(Jet1pt>1100)&&(Jet1pt<1700))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(deta<1.3)&&(DijetMass>2000)&&(Jet1pt>1100)&&(Jet1pt<1700)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
 	       ]
      colors=[4,2,1,6,2,2,6,6,6]
      styles=[2,1,3,2,1,3,2,1,3]
      widths=[2,1,1,2,1,1,2,1,1]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     results=[]
     means=[]
     rms=[]
     for plot in plots:
      canvas = TCanvas("","",0,0,200,200)
      canvas.SetLogy(False)
      legend=TLegend(0.4,0.6,0.85,0.9)
      dataPlotted=False
      counter=0
      integral=1
      originalIntegral={}
      maximum=0
      s=0
      hists=[]
      firsthist=None
      for sample in samples:
       s+=1
       for gen in sets:
 	if (names[plots.index(plot)]=="pt" or names[plots.index(plot)]=="eta" or names[plots.index(plot)]=="npu" or names[plots.index(plot)]=="npv" or "costheta" in names[plots.index(plot)] or "Phi" in names[plots.index(plot)] or "dR" in names[plots.index(plot)]) and gen=="Gen":
 	   continue
 	if names[plots.index(plot)]=="npu" and s==2:
 	   continue
 	if (names[plots.index(plot)]=="pt" or names[plots.index(plot)]=="eta") and gen=="lowPU":
 	   continue
 	if (runSet==2 or runSet==3) and gen!="" and s==2:
 	   continue
 	print sample, gen

 	f=TFile.Open(sample)
 	tree=f.Get("dijetWtag")

 	signal = "Hpp" in sample or "Py6" in sample
 	histname="plot"+names[plots.index(plot)]+gen+str(s)
 	if "sj angular resolution" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,0.2);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "sj p_{T} resolution (GeV)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-1000,1000);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "sj mass resolution (GeV)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-50,50);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "cos #theta" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "#Phi" in plot[2]:
 	   hist=TH1F(histname,histname,25,-3.15,3.15);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "#Delta R" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,3);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="pileup interactions":
 	   hist=TH1F(histname,histname,25,0,50);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="number of vertices":
 	   hist=TH1F(histname,histname,25,0,50);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet #eta":
 	   hist=TH1F(histname,histname,25,-2.4,2.4);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "C_{2}" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,0.8);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "jet charge (#kappa=0.3)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-4,4);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   hist.GetXaxis().SetRangeUser(-4,4)
 	if "jet charge (#kappa=0.5)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-2,2);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   hist.GetXaxis().SetRangeUser(-2,2)
 	if "jet charge (#kappa=1.0)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-1,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   hist.GetXaxis().SetRangeUser(-1,1)
 	if plot[2]=="jet constituents":
 	   hist=TH1F(histname,histname,25,0,200);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="charged particles (p_{T}^{rel}>0.1)":
 	   hist=TH1F(histname,histname,25,0,25);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="neutral particles (p_{T}^{rel}>0.1)":
 	   hist=TH1F(histname,histname,25,0,25);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="3rd charged particle p_{T}":
 	   hist=TH1F(histname,histname,25,0,250);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="3rd particle p_{T}":
 	   hist=TH1F(histname,histname,25,0,250);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "jet p_{T}" in plot[2] and not resolution:
 	   hist=TH1F(histname,histname,40,0,3000);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   canvas.SetLogy(True)
 	if "jet p_{T}" in plot[2] and resolution:
 	   hist=TH1F(histname,histname,40,0,3000);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	if "particle 1 p_{T}" in plot[2]:
 	   hist=TH1F(histname,histname,40,0,500);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	   #canvas.SetLogy(True)
 	if "particle 2 p_{T}" in plot[2]:
 	   hist=TH1F(histname,histname,40,0,500);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	   #canvas.SetLogy(True)
 	if "particle 3 p_{T}" in plot[2]:
 	   hist=TH1F(histname,histname,40,0,500);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	   #canvas.SetLogy(True)
 	if "pruned jet mass" in plot[2] or "trimmed jet mass" in plot[2]:
 	   hist=TH1F(histname,histname,50,0,150);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]== "jet mass (GeV)":
 	   hist=TH1F(histname,histname,50,0,300);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="mass drop":
 	   hist=TH1F(histname,histname,20,0,1);
 	   hist.GetYaxis().SetRangeUser(0,60000)
 	   if "aftermass" in names[plots.index(plot)]:
 	       hist.GetYaxis().SetRangeUser(0,6000)
 	if "#tau_{2}/#tau_{1}" in plot[2]:
 	   hist=TH1F(histname,histname,20,0,1);
 	   hist.GetYaxis().SetRangeUser(0,75000)
 	   if "aftermass" in names[plots.index(plot)]:
 	       hist.GetYaxis().SetRangeUser(0,5000)

 	if gen=="lowPU":
 	    variable,cutstring=plot[0],plot[1]+"&&(nPU<17)"
 	elif gen=="Subjet":
 	    variable,cutstring="Jet1MassSubjet",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="Angle":
 	    variable,cutstring="Jet1MassGenSubjetAngle",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="Pt":
 	    variable,cutstring="Jet1MassGenSubjetPt",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="Mass":
 	    variable,cutstring="Jet1MassGenSubjetMass",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="CHF1":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF<0.4)"
 	elif gen=="CHF2":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF>0.4)&&(Jet1CHF<0.6)"
 	elif gen=="CHF3":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF>0.6)&&(Jet1CHF<0.8)"
 	elif gen=="CHF4":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF>0.8)"
 	elif gen=="MassWindow":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1Mass>40)&&(Jet1Mass<60)"
 	elif gen=="PtWindow":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1pt>1500)"
 	elif gen=="barrel":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(Jet1eta)<1.0)"
 	elif gen=="endcap":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(Jet1eta)>1.0)"
 	elif gen=="EtaWindow":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(Jet1eta)<0.5)"
 	elif gen=="Dr01":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(parton_dR_1)>0.01)&&(abs(parton_dR_1)<0.14)"
 	elif gen=="Dr05":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(parton_dR_1)>0.14)&&(abs(parton_dR_1)<0.28)"
 	elif gen=="Dr10":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(parton_dR_1)>0.28)&&(abs(parton_dR_1)<1.0)"
 	elif "TrackMass" in gen or "CaloMass" in gen or "PrunedMass" in gen or "UnGroomedMass" in gen:
 	    variable,cutstring=gen,plot[1].replace("Jet","GenJet").replace("DijetMass","GenDijetMass").replace("deta","Gendeta")
 	elif gen=="Gen":
 	    variable,cutstring=gen+plot[0],plot[1].replace("Jet","GenJet").replace("DijetMass","GenDijetMass").replace("deta","Gendeta")
 	else:
 	    variable,cutstring=gen+plot[0],plot[1]
 	
 	#if "WW" in sample:
 	#  cutstring+="&&(Jet1genWhadronic==1)"
 	if resolution and variable=="Jet1PrunedMass":
	    if "WW" in sample:
	        variable="(Jet1PrunedMass-GenJet1Mass)"
 	    else:
	        variable="(Jet1PrunedMass-GenJet1Mass)/GenJet1Mass"
 	if resolution and variable=="Jet1UnGroomedMass":
	    if "WW" in sample:
                variable="(Jet1UnGroomedMass-GenJet1UnGroomedMass)"
 	    else:
 	        variable="(Jet1UnGroomedMass-GenJet1UnGroomedMass)/GenJet1UnGroomedMass"
 	if resolution and variable=="Jet1Mass":
	    if "WW" in sample:
 	        variable="(Jet1Mass-GenJet1Mass)"
 	    else:
 	        variable="(Jet1Mass-GenJet1Mass)/GenJet1Mass"
 	if resolution and variable=="Jet1pt":
 	    variable="(Jet1pt-GenJet1pt)/GenJet1pt"
 	
 	if resolution and "/" in variable:
           hist=TH1F(histname,histname,40,-0.5,0.5);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if resolution and not "/" in variable:
           hist=TH1F(histname,histname,50,-100,100);
 	   hist.GetYaxis().SetRangeUser(0,50000)

 	print histname,variable,cutstring
 	tree.Project(histname,variable,cutstring)
 	if runSet==32 or runSet==33 or runSet==34:
 	   hist.Rebin(2)
 	if "QCD" in sample:
 	    originalIntegral[histname]=hist.Integral()
 	hist.SetTitle("")
 	hist.SetFillStyle(0)
 	hist.SetMarkerStyle(20)
 	#hist.SetMarkerSize(2)
 	hist.GetXaxis().SetTitle(plot[2])
 	if resolution:
	  if "/" in variable:
 	    hist.GetXaxis().SetTitle("(reco-gen)/gen "+plot[2])
 	  else:
	    hist.GetXaxis().SetTitle("(reco-gen) "+plot[2])
 	hist.GetYaxis().SetTitle("Normalized Distribution")
 	if "Run" in sample:
 	    integral=hist.Integral()
 	if hist.Integral()>0:
 	    hist.Scale(integral/hist.Integral())

 	hists+=[hist]
	means+=[hist.GetMean()]
	rms+=[hist.GetRMS()]
        """
 	if "QCD1000" in sample:
 	    histname500="plot"+names[plots.index(plot)]+gen+str(s-1)
 	    for his in reversed(hists):
 		if histname500==his.GetName():
 		    oldIntegral=his.Integral()
 		    if his.Integral()>0:
 			his.Scale(originalIntegral[histname500]/his.Integral())
 		    if hist.Integral()>0:
 			hist.Scale(originalIntegral[histname]/hist.Integral())
 		    weight=204.0/13798133*30522161/8426.0
 		    his.Add(hist,weight)
 		    if oldIntegral>0:
 			his.Scale(oldIntegral/his.Integral())
 		    else:
 			his.Scale(integral/his.Integral())
 		    hist=his
 		    break
 	if "QCD500" in sample:
 	    continue
 	
 	if "QCDPythia8" in sample and not "170" in sample:
 	    samplenames=["170","300","470","600","800","1000","1400","1800"]
 	    samplenumbers=[800046,490042,500051,492988,400059,400050,200070,194313]
 	    samplecrossections=[37974.99,1938.868,124.8942,29.55049,3.871308,0.8031018,0.03637225,0.00197726]
 	    samplenumber=0
 	    for samplename in samplenames:
 	      if samplename in sample:
 		samplenumber=samplenames.index(samplename)
 	    histnameFirst="plot"+names[plots.index(plot)]+gen+str(s-samplenumber)
 	    for his in reversed(hists):
 		if histnameFirst==his.GetName():
 		    oldIntegral=his.Integral()
 		    if his.Integral()>0:
 			his.Scale(originalIntegral[histnameFirst]/his.Integral())
 		    if hist.Integral()>0:
 			hist.Scale(originalIntegral[histname]/hist.Integral())
 		    weight=samplecrossections[samplenumber]/samplenumbers[samplenumber]*samplenumbers[0]/samplecrossections[0]
 		    his.Add(hist,weight)
 		    if oldIntegral>0:
 			originalIntegral[histnameFirst]=his.Integral()
 			his.Scale(oldIntegral/his.Integral())
 		    elif his.Integral()>0:
 			originalIntegral[histnameFirst]=his.Integral()
 			his.Scale(integral/his.Integral())
 		    hist=his
 		    break
 	if "QCDPythia8" in sample and not "1800" in sample:
 	    continue
        """
 	hist.SetLineColor(colors[counter])
 	hist.SetLineStyle(styles[counter])	  
 	hist.SetLineWidth(widths[counter])
 	
 	if counter==0:
 	  firsthist=hist
 	  if "Run" in sample:
 	    hist.Draw("pe")
 	  elif "Gen" in gen:
 	    hist.Draw("chist")
 	  else:
 	    hist.Draw("hist")
 	else:
 	  if "Run" in sample:
 	    hist.Draw("pesame")
 	  elif "Gen" in gen:
 	    hist.Draw("csame")
 	  else:
 	    hist.Draw("histsame")

 	if hist.GetMaximum()>maximum and hist.GetMaximum()<hist.Integral():
 	    maximum=hist.GetMaximum()

        if resolution:
	    print "mean:", hist.GetMean()

 	if "jet p_{T}" in plot[2] and not resolution:
 	    firsthist.GetYaxis().SetRangeUser(0.001,maximum*20.0)
 	else:
 	    firsthist.GetYaxis().SetRangeUser(0,maximum*2.0)

 	if gen=="Gen" and "Hpp" in  sample:
 	  legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Herwig++","l")
 	elif gen=="Gen" and "Py6" in  sample:
 	  legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Pythia6","l")
 	elif runSet==32 and s==1:
 	  legend.AddEntry(hist,"default PF clusters","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==32 and s==2:
 	  legend.AddEntry(hist,"mod. HCAL clusters","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==32 and s==3:
 	  legend.AddEntry(hist,"no HCAL clusters","l")
 	  #legend.AddEntry(hist,"mod. ECAL+HCAL clusters","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==32 and s==4:
 	  legend.AddEntry(hist,"mod. block tracks","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==33 and s==1:
 	  legend.AddEntry(hist,"default PF clusters","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==33 and s==2:
 	  legend.AddEntry(hist,"mod. HCAL clusters","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==33 and s==3:
 	  legend.AddEntry(hist,"no HCAL clusters","l")
 	  #legend.AddEntry(hist,"mod. ECAL+HCAL clusters","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	elif runSet==33 and s==4:
 	  legend.AddEntry(hist,"mod. block tracks","l")
 	  legend.AddEntry(hist,"mean=%0.3f, RMS=%0.3f"%(means[-1],rms[-1]),"")
 	else:
 	  legend.AddEntry(hist," + <PU>=22 + sim.","l")
 	counter+=1

      legend.SetTextSize(0.03)
      legend.SetFillStyle(0)
      legend.Draw("same")

      legend4=TLegend(0.23,0.85,0.5,0.9,"CA R=0.8")
      legend4.SetTextSize(0.03)
      legend4.SetFillStyle(0)
      legend4.Draw("same")

      if runSet==33:
       legend2=TLegend(0.17,0.8,0.5,0.85,"1.1 < p_{T} < 1.7 TeV")
       legend2.SetTextSize(0.03)
       legend2.SetFillStyle(0)
       legend2.Draw("same")

      legend2a=TLegend(0.24,0.75,0.5,0.8,"|#eta|<2.4")
      legend2a.SetTextSize(0.03)
      legend2a.SetFillStyle(0)
      legend2a.Draw("same")

      if "parton_dR_1" in plot[1]:
 	legend2b=TLegend(0.17,0.7,0.5,0.75,"#DeltaR(partons) < 0.14")
 	legend2b.SetTextSize(0.03)
 	legend2b.SetFillStyle(0)
 	legend2b.Draw("same")

      banner = TLatex(0.24,0.93,"CMS Preliminary Simulation, #sqrt{s} = 8 TeV, dijets");
      banner.SetNDC()
      banner.SetTextSize(0.04)
      banner.Draw();  

      if "aftermass" in names[plots.index(plot)]:
 	 legend3=TLegend(0.17,0.7,0.5,0.75,"60 < m_{j} < 100 GeV")
 	 legend3.SetTextSize(0.03)
 	 legend3.SetFillStyle(0)
 	 legend3.Draw("same")

      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+filename+"_"+str(runSet)+str(int(resolution))+".png")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+filename+"_"+str(runSet)+str(int(resolution))+".pdf")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+filename+"_"+str(runSet)+str(int(resolution))+".root")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+filename+"_"+str(runSet)+str(int(resolution))+".C")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+filename+"_"+str(runSet)+str(int(resolution))+".eps")
