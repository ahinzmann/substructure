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
gStyle.SetPadRightMargin(0.10)
gStyle.SetMarkerSize(0.5)
gStyle.SetHistLineWidth(1)
#gStyle.SetStatFontSize(0.020)
gStyle.SetTitleSize(0.06, "XYZ")
gStyle.SetLabelSize(0.05, "XYZ")
gStyle.SetNdivisions(506, "XYZ")
gStyle.SetLegendBorderSize(0)

#TGaxis.SetMaxDigits(3)

#if __name__ == '__main__':

theory=False
for runSet in [1,2]:

 names = ["npv",
          "npu",
	   "pt",
	   "eta",
	   ]
 plots = [("numberOfPrimaryVertices","vertexWeight*((abs(Jet1eta)<2.4))","number of vertices"),
           ("nPU","vertexWeight*((abs(Jet1eta)<2.4))","number of PU interactions"),
           ("Jet1pt","vertexWeight*((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
           ("Jet1eta","vertexWeight*((abs(Jet1eta)<2.4))","jet #eta"),
           ]

 jetmasscut="&&(Jet1Mass>60)&&(Jet1Mass<100)"


 if runSet==1:
  massbins=[250,500,750,1000,1500,2000,2500,3000,3500,4000]
  samples = [#"substructure_pas_WW2000_posHCAL.root",
             #"substructure_pas_WW3000_posHCAL.root",
             #"substructure_pas_WW4000_posHCAL.root",
             #"substructure_pas_qW5000_posHCAL.root",
             #"substructure_pas_qW7000_posHCAL.root",
             "substructure_pas_WW1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW2000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW3000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW4000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_qW5000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_qW7000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             ]
  colors=[1,1,2,2,1,1,2,2,1,1,2,2,]
  styles=[2,1,2,1,2,1,2,1,2,1,2,1,]
  widths=[1,2,1,2,2,1,2,1,2,1,2,1,]
  #colors=[2,1,2,1,2,1,]
  #styles=[2,1,2,1,2,1,]
  #widths=[2,1,2,1,2,1,]

 if runSet==2:
  massbins=[800,1200,1600,2200,3000]
  samples = [#"substructure_pas_QCD30_posHCAL.root",
             #"substructure_pas_QCD170_posHCAL.root",
             #"substructure_pas_QCD1000_posHCAL.root",
             #"substructure_pas_QCD1800_posHCAL.root",
             #"substructure_pas_QCD170_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_QCD1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_QCD1800_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
            ]
  colors=[1,2,4,6,1,1,2,4,6,1,1,2,4,6,1]
  styles=[2,1,2,1,1,1,1,2,3,1,1,1,2,3,1]
  widths=[1,2,1,2,2,2,2,2,2,2,2,2,2,2,2]

 results=[]
 for plot in plots:
  if runSet==3:
    canvas = TCanvas("","",0,0,200,260)
    canvas.Divide(1,2,0,0,0)
    canvas.GetPad(1).SetPad(0.0,0.28,1.0,1.0)
    canvas.GetPad(1).SetLeftMargin(0.15)
    canvas.GetPad(1).SetRightMargin(0.08)
    canvas.GetPad(1).SetTopMargin(0.08)
    canvas.GetPad(1).SetBottomMargin(0.05)
    canvas.GetPad(2).SetPad(0.0,0.0,1.0,0.28)
    canvas.GetPad(2).SetLeftMargin(0.15)
    canvas.GetPad(2).SetRightMargin(0.08)
    canvas.GetPad(2).SetTopMargin(0.08)
    canvas.GetPad(2).SetBottomMargin(0.45)
    canvas.cd(1)
    canvas.GetPad(1).SetLogy(False)
  else:
    canvas = TCanvas("","",0,0,200,200)
    canvas.SetLogy(False)
  legend=TLegend(0.15,0.7,0.85,0.9)
  denominator={}
  dataPlotted=False
  hists=[]
  fractions1=[]
  fractions2=[]
  firsthist=None
  counter=0
  counter2=0
  maximum=0
  for nominator in [0,1,2]:
   s=0
   firstQCD=True
   for sample in samples:
    s+=1
    print sample, nominator

    f=TFile.Open(sample)
    tree=f.Get("dijetWtag")

    signal = "Hpp" in sample or "Py6" in sample or "Bulk" in sample or "SM" in sample or "PS" in sample or "W" in sample
    histname="plot"+names[plots.index(plot)]+"_"+str(nominator)+str(s)
    if plot[2]=="number of vertices" and (runSet!=1 and runSet<5):
       hist=TH1F(histname,histname,15,5,50);
       hist.GetYaxis().SetRangeUser(0,50000)
    if plot[2]=="number of vertices" and (runSet==1 or runSet>=5):
       hist=TH1F(histname,histname,6,0,50);
       hist.GetYaxis().SetRangeUser(0,50000)
    if plot[2]=="number of PU interactions" and runSet==1:
       hist=TH1F(histname,histname,6,20,50);
       hist.GetYaxis().SetRangeUser(0,50000)
    elif plot[2]=="number of PU interactions":
       hist=TH1F(histname,histname,3,20,50);
       hist.GetYaxis().SetRangeUser(0,50000)
    if plot[2]=="jet #eta" and (runSet!=1 and runSet<5):
       hist=TH1F(histname,histname,20,-2.4,2.4);
       hist.GetYaxis().SetRangeUser(0,50000)
    if plot[2]=="jet #eta" and (runSet==1 or runSet>=5):
       hist=TH1F(histname,histname,10,-2.4,2.4);
       hist.GetYaxis().SetRangeUser(0,50000)
    if "jet p_{T}" in plot[2]:
       binning=array.array('d')
       for bin in massbins:
          binning.append(bin)
       hist=TH1F(histname,histname,len(binning)-1,binning);
       hist.GetYaxis().SetRangeUser(0,50000)

    variable,cutstring=plot[0],plot[1]
    if "WW" in sample or "qW" in sample:
        cutstring+="&&(Jet1genWhadronic==1)"
    if not "jet p_{T}" in plot[2]:
        cutstring+="&&(Jet1pt<1300)"
    if nominator==1:
        cutstring+=jetmasscut
    if nominator==2:
        cutstring+=jetmasscut+"&&(Jet1Nsub<0.6)"
    if (runSet==3 and s==1) or (runSet==4 and s<=2):
        cutstring+="&&(Jet1quarkgluon==2)"
    if (runSet==3 and s==2) or (runSet==4 and s>=3):
        cutstring+="&&(Jet1quarkgluon==1)"
    print histname,variable,cutstring
    hist.Sumw2()
    tree.Project(histname,variable,cutstring)
    hist.SetTitle("")
    hist.SetFillStyle(0)
    if nominator<2:
        hist.SetMarkerStyle(20)
    else:
        hist.SetMarkerStyle(21)
    #hist.SetMarkerSize(2)
    if runSet==3:
      hist.GetXaxis().SetTitle("")
      hist.GetXaxis().SetLabelColor(0)
    else:
      hist.GetXaxis().SetTitle(plot[2])
    if (runSet==1 or runSet>=5):
        hist.GetYaxis().SetTitle("Efficiency")
    if (runSet!=1 and runSet<5):
        hist.GetYaxis().SetTitle("Fake rate")

    print "mean",hist.GetMean()

    hists+=[hist]

    if "QCD" in sample and not firstQCD and not "flat" in sample:
        samplenames=["1000","1800"]
	samplenumbers=[1,1]
	samplecrossections=[1,2]
	samplenumber=0
        for samplename in samplenames:
          if samplename in sample:
            samplenumber=samplenames.index(samplename)
        histnameFirst="plot"+names[plots.index(plot)]+"_"+str(nominator)+str(s-samplenumber)
        for his in reversed(hists):
	    if histnameFirst==his.GetName():
                weight=samplecrossections[samplenumber]/samplenumbers[samplenumber]*samplenumbers[0]/samplecrossections[0]
	        his.Add(hist,weight)
 	        hist=his
		break
    if "QCD" in sample and not "1800" in sample and not "flat" in sample:
        firstQCD=False
        continue

    if runSet==1 and not "1000" in sample:
        samplenames=["1000","2000","3000","4000","5000","7000"]
	samplenumber=0
        for samplename in samplenames:
          if samplename in sample:
            samplenumber=samplenames.index(samplename)
        histnameFirst="plot"+names[plots.index(plot)]+"_"+str(nominator)+str(s-samplenumber)
        for his in reversed(hists):
	    if histnameFirst==his.GetName():
                weight=1
	        his.Add(hist,weight)
 	        hist=his
		break
    if runSet==1 and not "7000" in sample:
        continue

    hist.SetLineColor(colors[counter])
    hist.SetLineStyle(styles[counter])        
    hist.SetLineWidth(widths[counter])

    if not nominator:
        denominator[hist.GetName().split("_")[0]+"_"+str(s)]=hist
	continue
    else:
        clone=hist.Clone(hist.GetName()+"eff")
        clone.Divide(clone,denominator[hist.GetName().split("_")[0]+"_"+str(s)])
	if nominator==1:
            fractions1+=[clone]
	if nominator==2:
            fractions2+=[clone]
        for b in range(clone.GetNbinsX()):
          if clone.GetBinContent(b+1)>0:
            clone.SetBinError(b+1,clone.GetBinContent(b+1)*hist.GetBinError(b+1)/hist.GetBinContent(b+1))
	hist=clone
    
    if runSet==3 and nominator==2:
      canvas.cd(2)
      ratio=hist.Clone(hist.GetName()+"clone")
      hists+=[ratio]
      ratio.Divide(fractions2[0],hist)
      for b in range(hist.GetNbinsX()):
        if fractions2[0].GetBinContent(b+1)>0:
          ratio.SetBinError(b+1,fractions2[0].GetBinError(b+1)/fractions2[0].GetBinContent(b+1))
      ratio.GetYaxis().SetTitle("Data / Sim")
      ratio.GetYaxis().SetTitleSize(0.13)
      ratio.GetYaxis().SetTitleOffset(0.5)
      ratio.SetMarkerSize(0.1)
      ratio.GetYaxis().SetLabelSize(0.14)
      ratio.GetYaxis().SetRangeUser(0,2)
      ratio.GetYaxis().SetNdivisions(503)
      ratio.GetXaxis().SetLabelColor(1)
      ratio.GetXaxis().SetTitle(plot[2])
      ratio.GetXaxis().SetTitleSize(0.16)
      ratio.GetXaxis().SetTitleOffset(0.8)
      ratio.GetXaxis().SetLabelSize(0.14)
      print "now"
      if counter2==0:
        ratio.Draw("histe")
      else:
        ratio.Draw("histsame")
      counter2+=1
      #line=TLine(ratio.GetXaxis().GetBinLowEdge(1),1,ratio.GetXaxis().GetBinLowEdge(ratio.GetNbinsX()+1),1)
      #hists+=[line]
      #line.Draw("same")
      canvas.cd(1)
      if firsthist:
          firsthist.GetYaxis().SetTitleOffset(1.2)

    print "first bin",hist.GetBinContent(1)

    if counter==0:
      firsthist=hist
      if "Run" in sample:
        hist.Draw("pe")
      else:
        hist.Draw("he")
    else:
      if "Run" in sample:
        hist.Draw("pesame")
      else:
        hist.Draw("hesame")

    if hist.GetMaximum()>maximum and hist.GetMaximum()<hist.Integral():
        maximum=hist.GetMaximum()

    if (runSet!=1 and runSet<5):
        firsthist.GetYaxis().SetRangeUser(0,0.3)
    else:
        firsthist.GetYaxis().SetRangeUser(0,1)

    if "QCD" in sample and nominator==1 and "split" in sample:
      legend.AddEntry(hist,"QCD Pythia8: m_{pruned} cut","l")
    elif "QCD" in sample and nominator==2 and "split" in sample:
      legend.AddEntry(hist,"QCD Pythia8: m_{pruned} & #tau_{2}/#tau_{1} cut","l")
    elif "W" in sample and nominator==1 and "split" in sample:
        legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Pythia8: m_{pruned} cut","l")
    elif "W" in sample and nominator==2 and "split" in sample:
        legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Pythia8: m_{pruned} & #tau_{2}/#tau_{1} cut","l")
    elif "QCD" in sample and nominator==1:
      legend.AddEntry(hist,"QCD Pythia8: m_{pruned} cut (default PF)","l")
    elif "QCD" in sample and nominator==2:
      legend.AddEntry(hist,"QCD Pythia8: m_{pruned} & #tau_{2}/#tau_{1} cut (default PF)","l")
    elif "W" in sample and nominator==1:
        legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Pythia8: m_{pruned} cut (default PF)","l")
    elif "W" in sample and nominator==2:
        legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Pythia8: m_{pruned} & #tau_{2}/#tau_{1} cut (default PF)","l")
    counter+=1

  legend.SetTextSize(0.03)
  legend.SetFillStyle(0)
  legend.Draw("same")

  #if (runSet!=1 and runSet<5):
  legend4=TLegend(0.23,0.85,0.5,0.9,"CA R=0.8")
  #else:
  #    legend4=TLegend(0.43,0.45,0.5,0.5,"CA R=0.8")
  legend4.SetTextSize(0.03)
  legend4.SetFillStyle(0)
  #legend4.Draw("same")

  if not "jet p_{T}" in plot[2]:
    #if (runSet!=1 and runSet<5):
    legend2=TLegend(0.17,0.8,0.5,0.85,"800 < p_{T} < 1000 GeV")
    #else:
    #   legend2=TLegend(0.37,0.4,0.5,0.45,"800 < p_{T} < 1000 GeV")
    legend2.SetTextSize(0.03)
    legend2.SetFillStyle(0)
    #legend2.Draw("same")

  #if (runSet!=1 and runSet<5):
  legend2a=TLegend(0.24,0.75,0.5,0.8,"|#eta|<2.4")
  #else:
  #   legend2a=TLegend(0.44,0.35,0.5,0.4,"|#eta|<2.4")
  legend2a.SetTextSize(0.03)
  legend2a.SetFillStyle(0)
  #legend2a.Draw("same")

  #if runSet==2:
  #  banner = TLatex(0.27,0.93,"CMS Preliminary, 19.6 fb^{-1}, #sqrt{s} = 8 TeV, dijets");
  #else:
  banner = TLatex(0.24,0.93,"CMS Preliminary Simulation, #sqrt{s} = 13 TeV");
  banner.SetNDC()
  banner.SetTextSize(0.04)
  banner.Draw();  

  canvas.SaveAs("substructure_pas_"+names[plots.index(plot)]+"_eff"+str(runSet+100*theory)+".png")
  canvas.SaveAs("substructure_pas_"+names[plots.index(plot)]+"_eff"+str(runSet+100*theory)+".pdf")
  canvas.SaveAs("substructure_pas_"+names[plots.index(plot)]+"_eff"+str(runSet+100*theory)+".root")
  canvas.SaveAs("substructure_pas_"+names[plots.index(plot)]+"_eff"+str(runSet+100*theory)+".C")
  canvas.SaveAs("substructure_pas_"+names[plots.index(plot)]+"_eff"+str(runSet+100*theory)+".eps")
