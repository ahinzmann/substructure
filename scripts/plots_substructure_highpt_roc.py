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
gStyle.SetPadBottomMargin(0.13)
gStyle.SetPadTopMargin(0.07)
gStyle.SetPadRightMargin(0.07)
gStyle.SetMarkerSize(0.5)
gStyle.SetHistLineWidth(1)
#gStyle.SetStatFontSize(0.020)
gStyle.SetTitleSize(0.06, "XYZ")
gStyle.SetLabelSize(0.05, "XYZ")
gStyle.SetNdivisions(506, "XYZ")
gStyle.SetLegendBorderSize(0)

TGaxis.SetMaxDigits(3)

if __name__ == '__main__':

 scenario=""

 selection="(abs(Jet1eta)<2.4)&&(deta<1.3)&&(DijetMass>890)&&(Jet1pt>1600)&&(Jet1pt<2400)"
 selection_mass="&&(Jet1Mass>60)&&(Jet1Mass<100)"
 plots=[("GenJet1Nsub","Gen-jets 0.8 < p_{T} < 1.2 TeV",0,1,[
             "substructure_pas_QCD1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW2000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",]),
        #("Jet1Nsub","default PF (0.8 < p_{T} < 1.2 TeV)",0,1,[
        #     "substructure_pas_QCD1000_posHCAL.root",
        #     "substructure_pas_WW2000_posHCAL.root",]),
        ("Jet1Nsub","PF-jets 0.8 < p_{T} < 1.2 TeV",0,1,[
             "substructure_pas_QCD1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW2000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",]),
        ("GenJet1Nsub","Gen-jets 1.6 < p_{T} < 2.4 TeV",0,1,[
             "substructure_pas_QCD1800_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW4000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",]),
        #("Jet1Nsub","default PF (1.6 < p_{T} < 2.4 TeV)",0,1,[
        #     "substructure_pas_QCD1800_posHCAL.root",
        #     "substructure_pas_WW4000_posHCAL.root",]),
        ("Jet1Nsub","PF-jets 1.6 < p_{T} < 2.4 TeV",0,1,[
             "substructure_pas_QCD1800_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
             "substructure_pas_WW4000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",]),
        ]

 names = ["lowPtgen",
          #"lowPtold",
          "lowPtnew",
	  "gen",
          #"old",
          "new",
          ]

 colors=[2,3,4,6,7,9,15]
 widths=[2,3,2,3,2,2,2]
 styles=[2,1,2,1,5,6,7]
 sizes=[0.6,0.4,0.4,0.6,0.3,0.3,0.4]
           
 results=[]

 canvas = TCanvas("","",0,0,200,210)
 canvas.SetLogy(False)
 mg = TMultiGraph()
 legend=TLegend(0.2,0.2,0.6,0.5,"W_{T}, <PU> = 40")
 legendb=TLegend(0.2,0.2,0.6,0.5," ")

 for plot in plots:
  event_count=[]
  for sample in plot[4]:
    sel=selection
    sel_mass=selection_mass
    if "lowPt" in names[plots.index(plot)]:
      sel=sel.replace("(Jet1pt>1600)&&(Jet1pt<2400)","(Jet1pt>800)&&(Jet1pt<1200)")
    if "gen" in names[plots.index(plot)]:
      sel_mass=sel_mass.replace("Jet1Mass","GenJet1Mass")
    if "WW" in sample or "qW" in sample:
      sel+="&&(Jet1genWhadronic==1)"
    f=TFile.Open(sample)
    tree=f.Get("dijetWtag")
    hist=TH1F("DijetMass","DijetMass",10000,0,10000);
    if "gen" in names[plots.index(plot)]:
        print sample,"GenDijetMass",sel
        tree.Project("DijetMass","GenDijetMass",sel)
    else:
        print sample,"DijetMass",sel
        tree.Project("DijetMass","DijetMass",sel)
    before=hist.Integral()
    print "before mass cut",before
    histname="plot"+names[plots.index(plot)]
    hist=TH1F(histname,histname,10000,plot[2],plot[3]);
    print sample,plot[0],sel+sel_mass
    tree.Project(histname,plot[0],sel+sel_mass)
    after=hist.Integral()
    print "after mass cut",after
    integral=[]
    for b in range(hist.GetNbinsX()):
        integral+=[hist.Integral(0,b+1)]
    event_count+=[[before,after,integral]]

  groc = TGraphErrors(1)
  groc.SetLineColor(colors[plots.index(plot)])
  groc.SetLineWidth(widths[plots.index(plot)])
  groc.SetLineStyle(styles[plots.index(plot)])
  for b in range(len(event_count[0][2])):
      groc.SetPoint(b, event_count[1][2][b]/event_count[1][0], 1.-event_count[0][2][b]/event_count[0][0])
  mg.Add(groc,"L")
  legend.AddEntry(groc,plot[1],"l")

  groc2 = TGraph(1)
  groc2.SetMarkerColor(colors[plots.index(plot)])
  groc2.SetMarkerStyle(20)
  groc2.SetMarkerSize(sizes[plots.index(plot)])
  groc2.SetPoint(0, event_count[1][2][-1]/event_count[1][0], groc.Eval(event_count[1][2][-1]/event_count[1][0]))
  mg.Add(groc2,"P")

  groc3 = TGraph(1)
  groc3.SetMarkerColor(colors[plots.index(plot)])
  groc3.SetMarkerStyle(21)
  groc3.SetMarkerSize(sizes[plots.index(plot)])
  groc3.SetPoint(0, event_count[1][2][int(len(event_count[0][2])*0.6)]/event_count[1][0], groc.Eval(event_count[1][2][int(len(event_count[0][2])*0.6)]/event_count[1][0]))
  mg.Add(groc3,"P")
  legendb.AddEntry(groc2," ","p")

 mg.SetTitle("")
 mg.Draw("AP")
 mg.GetXaxis().SetTitle("#epsilon_{sig}")
 mg.GetYaxis().SetTitle("1 - #epsilon_{bkg}")
 mg.GetXaxis().SetRangeUser(0,1)
 mg.GetYaxis().SetRangeUser(0.8,1)

 legend.SetTextSize(0.036)
 legend.SetFillStyle(0)
 legend.Draw("same")

 legendb.SetTextSize(0.036)
 legendb.SetFillStyle(0)
 legendb.Draw("same")

 groc5 = TGraph(1)
 groc5.SetMarkerColor(1)
 groc5.SetMarkerStyle(20)

 groc3 = TGraph(1)
 groc3.SetLineColor(1)
 groc3.SetLineWidth(2)
 groc3.SetLineStyle(1)

 groc4 = TGraph(1)
 groc4.SetMarkerColor(1)
 groc4.SetMarkerStyle(21)

 legend3=TLegend(0.2,0.55,0.6,0.7)
 legend3.AddEntry(groc5,"60 < m_{J} < 100 GeV","p")
 legend3.AddEntry(groc3," & #tau_{21} < cut","l")
 legend3.AddEntry(groc4," & #tau_{21} < 0.6","p")
 legend3.SetTextSize(0.036)
 legend3.SetFillStyle(0)
 legend3.Draw("same")

 legend4=TLegend(0.2,0.85,0.9,0.9,"CA R=0.8")
 legend4.SetTextSize(0.03)
 legend4.SetFillStyle(0)
 legend4.Draw("same")

 legend2a=TLegend(0.2,0.8,0.9,0.85,"|#eta|<2.4")
 legend2a.SetTextSize(0.03)
 legend2a.SetFillStyle(0)
 legend2a.Draw("same")

 banner = TLatex(0.16,0.93,"CMS Preliminary Simulation, #sqrt{s} = 13 TeV");
 banner.SetNDC()
 banner.SetTextSize(0.04)
 banner.Draw();  

 canvas.SaveAs("substructure_pas_roc3"+scenario+".png")
 canvas.SaveAs("substructure_pas_roc3"+scenario+".pdf")
 canvas.SaveAs("substructure_pas_roc3"+scenario+".root")
 canvas.SaveAs("substructure_pas_roc3"+scenario+".C")
 canvas.SaveAs("substructure_pas_roc3"+scenario+".eps")
