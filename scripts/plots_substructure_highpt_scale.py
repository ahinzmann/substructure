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

 for variable in ["mass","ungroomedmass","pt"]:
   for quantity in ["scale","resolution"]:
     canvas = TCanvas("","",0,0,200,210)
     canvas.SetLogx(True)
     mg = TMultiGraph()
     legend=TLegend(0.2,0.2,0.6,0.5,"<PU>=0")
     legendb=TLegend(0.2,0.2,0.6,0.5,"")

     g = TGraphErrors(0)
     g.SetLineColor(1)
     g.SetMarkerStyle(24)
     g0 = TGraphErrors(0)
     g0.SetLineColor(1)
     g0.SetMarkerStyle(24)
     g1 = TGraphErrors(0)
     g1.SetLineColor(2)
     g1.SetMarkerStyle(25)
     g15 = TGraphErrors(0)
     g15.SetLineColor(4)
     g15.SetMarkerStyle(26)
     gq0 = TGraphErrors(0)
     gq0.SetLineColor(1)
     gq0.SetLineStyle(2)
     gq0.SetMarkerStyle(24)
     gq1 = TGraphErrors(0)
     gq1.SetLineColor(2)
     gq1.SetLineStyle(2)
     gq1.SetMarkerStyle(25)
     gq15 = TGraphErrors(0)
     gq15.SetLineColor(4)
     gq15.SetLineStyle(2)
     gq15.SetMarkerStyle(26)
     gq = TGraphErrors(0)
     gq.SetLineColor(1)
     gq.SetLineStyle(2)
     gq.SetMarkerStyle(24)
     f=open("scale.txt")
     for l in f.readlines():
       if quantity=="scale" and not "mean" in l: continue
       if quantity=="resolution" and not "rms" in l: continue
       mean=float(l.split(" ")[-2])
       mean_err=float(l.split(" ")[-1])
       w=False
       if "WW1000" in l:
 	 pt=0.5
 	 w=True
       if "WW2000" in l:
 	 pt=1
 	 w=True
       if "WW3000" in l:
 	 pt=1.5
 	 w=True
       if "WW4000" in l:
 	 pt=2
 	 w=True
       if "qW5000" in l:
 	 pt=2.5
 	 w=True
	 continue
       if "qW7000" in l:
 	 pt=3.5
 	 w=True
       if "QCD170" in l:
 	 pt=0.2
       if "QCD1000" in l:
 	 pt=1
       if "QCD1800" in l:
 	 pt=2
       if l.startswith("32") and " "+variable+" " in l and w:
 	 g0.SetPoint(g0.GetN(), pt, mean)
 	 g0.SetPointError(g0.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("33") and " "+variable+" " in l and w:
 	 g1.SetPoint(g1.GetN(), pt, mean)
 	 g1.SetPointError(g1.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("34") and " "+variable+" " in l and w:
 	 g15.SetPoint(g15.GetN(), pt, mean)
 	 g15.SetPointError(g15.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("35") and " "+variable+" " in l and w:
 	 g.SetPoint(g.GetN(), pt, mean)
 	 g.SetPointError(g.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("32") and " "+variable+" " in l and not w:
 	 gq0.SetPoint(gq0.GetN(), pt, mean)
 	 gq0.SetPointError(gq0.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("33") and " "+variable+" " in l and not w:
 	 gq1.SetPoint(gq1.GetN(), pt, mean)
 	 gq1.SetPointError(gq1.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("34") and " "+variable+" " in l and not w:
 	 gq15.SetPoint(gq15.GetN(), pt, mean)
 	 gq15.SetPointError(gq15.GetN()-1, 0, mean_err)
 	 print w,pt,mean
       if l.startswith("35") and " "+variable+" " in l and not w:
 	 gq.SetPoint(gq.GetN(), pt, mean)
 	 gq.SetPointError(gq.GetN()-1, 0, mean_err)
 	 print w,pt,mean
     if quantity=="scale":
       mg.Add(g0,"PL")
       mg.Add(g1,"PL")
       mg.Add(g15,"PL")
       #mg.Add(gq0,"PL")
       #mg.Add(gq1,"PL")
       #mg.Add(gq15,"PL")
       mg.Add(gq,"PL")
       legend.AddEntry(g0,"W-jet |#eta|<1.0","l")
       legend.AddEntry(g1,"W-jet 1.0<|#eta|<1.5","l")
       legend.AddEntry(g15,"W-jet 1.5<|#eta|<2.4","l")
       #legend.AddEntry(gq0,"q/g-jet |#eta|<1.0","l")
       #legend.AddEntry(gq1,"q/g-jet 1.0<|#eta|<1.5","l")
       #legend.AddEntry(gq15,"q/g-jet 1.5<|#eta|<2.4","l")
       legend.AddEntry(gq,"q/g-jet |#eta|<2.4","l")
     else:
       mg.Add(g,"PL")
       mg.Add(gq,"PL")
       legend.AddEntry(g,"W-jet |#eta|<2.4","l")
       legend.AddEntry(gq,"q/g-jet |#eta|<2.4","l")

     mg.SetTitle("")
     mg.Draw("APL")
     mg.GetXaxis().SetTitle("p_{T} (TeV)")
     mg.GetXaxis().SetMoreLogLabels()
     if variable=="mass":
       mg.GetYaxis().SetTitle("pruned jet mass "+quantity)
     if variable=="ungroomedmass":
       mg.GetYaxis().SetTitle("jet mass "+quantity)
     if variable=="pt":
       mg.GetYaxis().SetTitle("jet p_{T} "+quantity)
     mg.GetXaxis().SetRangeUser(0.2,4)
     if quantity=="scale" and variable=="ungroomedmass":
       mg.GetYaxis().SetRangeUser(0.7,1.5)
     elif quantity=="scale":
       mg.GetYaxis().SetRangeUser(0.8,1.1)
     elif variable=="pt":
       mg.GetYaxis().SetRangeUser(0,0.1)
     elif variable=="ungroomedmass":
       mg.GetYaxis().SetRangeUser(0,0.25)
     else:
       mg.GetYaxis().SetRangeUser(0,0.2)

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

     canvas.SaveAs("substructure_pas_scale_"+variable+"_"+quantity+".png")
     canvas.SaveAs("substructure_pas_scale_"+variable+"_"+quantity+".pdf")
     canvas.SaveAs("substructure_pas_scale_"+variable+"_"+quantity+".root")
     canvas.SaveAs("substructure_pas_scale_"+variable+"_"+quantity+".C")
     canvas.SaveAs("substructure_pas_scale_"+variable+"_"+quantity+".eps")
