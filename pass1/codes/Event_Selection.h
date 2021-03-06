//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 19 21:23:53 2018 by ROOT version 6.12/06
// from TChain Event_Selection/
//////////////////////////////////////////////////////////

#ifndef Event_Selection_h
#define Event_Selection_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Event_Selection {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           nTrk;
   Int_t           nPos;
   Int_t           nCl;
   Char_t          isCalib;
   Char_t          isPulser;
   Char_t          isSingle0;
   Char_t          isSingle1;
   Char_t          isPair0;
   Char_t          isPair1;
   Double_t        evTime;
   Int_t           evTx;
   Int_t           evTy;
   Double_t        rfT1;
   Double_t        rfT2;
   Int_t           nEcalHits;
   Int_t           nSVTHits;
   Int_t           nEcalCl;
   Int_t           nEcalClele;
   Int_t           nEcalClpos;
   Int_t           nEcalClpho;
   Int_t           nEcalClEleSide;
   Int_t           nEcalClPosSide;
   Int_t           nSVTHitsL1;
   Int_t           nSVTHitsL2;
   Int_t           nSVTHitsL3;
   Int_t           nSVTHitsL4;
   Int_t           nSVTHitsL5;
   Int_t           nSVTHitsL6;
   Int_t           nSVTHitsL1b;
   Int_t           nSVTHitsL2b;
   Int_t           nSVTHitsL3b;
   Int_t           nSVTHitsL4b;
   Int_t           nSVTHitsL5b;
   Int_t           nSVTHitsL6b;
   Double_t        topL1HitX;
   Double_t        topL1HitY;
   Double_t        botL1HitX;
   Double_t        botL1HitY;
   Double_t        uncPX;
   Double_t        uncPY;
   Double_t        uncPZ;
   Double_t        uncP;
   Double_t        uncVX;
   Double_t        uncVY;
   Double_t        uncVZ;
   Double_t        uncChisq;
   Double_t        uncM;
   Double_t        bscPX;
   Double_t        bscPY;
   Double_t        bscPZ;
   Double_t        bscP;
   Double_t        bscVX;
   Double_t        bscVY;
   Double_t        bscVZ;
   Double_t        bscChisq;
   Double_t        bscM;
   Double_t        tarPX;
   Double_t        tarPY;
   Double_t        tarPZ;
   Double_t        tarP;
   Double_t        tarVX;
   Double_t        tarVY;
   Double_t        tarVZ;
   Double_t        tarChisq;
   Double_t        tarM;
   Double_t        vzcPX;
   Double_t        vzcPY;
   Double_t        vzcPZ;
   Double_t        vzcP;
   Double_t        vzcVX;
   Double_t        vzcVY;
   Double_t        vzcVZ;
   Double_t        vzcChisq;
   Double_t        vzcM;
   Double_t        uncCovXX;
   Double_t        uncCovXY;
   Double_t        uncCovXZ;
   Double_t        uncCovYX;
   Double_t        uncCovYY;
   Double_t        uncCovYZ;
   Double_t        uncCovZX;
   Double_t        uncCovZY;
   Double_t        uncCovZZ;
   Double_t        uncElePX;
   Double_t        uncElePY;
   Double_t        uncElePZ;
   Double_t        uncPosPX;
   Double_t        uncPosPY;
   Double_t        uncPosPZ;
   Double_t        uncEleP;
   Double_t        uncPosP;
   Double_t        bscElePX;
   Double_t        bscElePY;
   Double_t        bscElePZ;
   Double_t        bscPosPX;
   Double_t        bscPosPY;
   Double_t        bscPosPZ;
   Double_t        bscEleP;
   Double_t        bscPosP;
   Double_t        tarElePX;
   Double_t        tarElePY;
   Double_t        tarElePZ;
   Double_t        tarPosPX;
   Double_t        tarPosPY;
   Double_t        tarPosPZ;
   Double_t        tarEleP;
   Double_t        tarPosP;
   Double_t        vzcElePX;
   Double_t        vzcElePY;
   Double_t        vzcElePZ;
   Double_t        vzcPosPX;
   Double_t        vzcPosPY;
   Double_t        vzcPosPZ;
   Double_t        vzcEleP;
   Double_t        vzcPosP;
   Double_t        uncEleWtP;
   Double_t        uncPosWtP;
   Double_t        bscEleWtP;
   Double_t        bscPosWtP;
   Double_t        tarEleWtP;
   Double_t        tarPosWtP;
   Double_t        vzcEleWtP;
   Double_t        vzcPosWtP;
   Double_t        uncWtM;
   Double_t        bscWtM;
   Double_t        tarWtM;
   Double_t        vzcWtM;
   Double_t        elePX;
   Double_t        elePY;
   Double_t        elePZ;
   Double_t        eleP;
   Double_t        eleTrkChisq;
   Int_t           eleTrkHits;
   Int_t           eleTrkType;
   Double_t        eleTrkT;
   Double_t        eleTrkTsd;
   Double_t        eleTrkZ0;
   Double_t        eleTrkLambda;
   Double_t        eleTrkD0;
   Double_t        eleTrkPhi;
   Double_t        eleTrkOmega;
   Double_t        eleTrkEcalX;
   Double_t        eleTrkEcalY;
   Char_t          eleHasL1;
   Char_t          eleHasL2;
   Char_t          eleHasL3;
   Char_t          eleHasL4;
   Char_t          eleHasL5;
   Char_t          eleHasL6;
   Double_t        eleFirstHitX;
   Double_t        eleFirstHitY;
   Double_t        eleFirstHitT1;
   Double_t        eleFirstHitT2;
   Double_t        eleFirstHitDEDx1;
   Double_t        eleFirstHitDEDx2;
   Int_t           eleFirstClusterSize1;
   Int_t           eleFirstClusterSize2;
   Int_t           eleNHitsShared;
   //Double_t        eleHitsSharedP;
   Double_t        eleLambdaKink1;
   Double_t        eleLambdaKink2;
   Double_t        eleLambdaKink3;
   Double_t        elePhiKink1;
   Double_t        elePhiKink2;
   Double_t        elePhiKink3;
   Double_t        eleIsoStereo;
   Double_t        eleIsoAxial;
   Double_t        eleMinPositiveIso;
   Double_t        eleMinNegativeIso;
   Double_t        eleTrkExtrpXL0;
   Double_t        eleTrkExtrpYL0;
   Double_t        eleTrkExtrpXL1;
   Double_t        eleTrkExtrpYL1;
   Double_t        eleTrkExtrpXL2;
   Double_t        eleTrkExtrpYL2;
   Double_t        eleRawMaxAmplL1;
   Double_t        eleRawT0L1;
   Double_t        eleRawChisqL1;
   Double_t        eleRawTDiffL1;
   Double_t        eleRawMaxAmplL2;
   Double_t        eleRawT0L2;
   Double_t        eleRawChisqL2;
   Double_t        eleRawTDiffL2;
   Double_t        eleRawMaxAmplL3;
   Double_t        eleRawT0L3;
   Double_t        eleRawChisqL3;
   Double_t        eleRawTDiffL3;
   Int_t           eleNTrackHits;
   Double_t        eleHitsSharedP;
   Int_t           eleMaxHitsShared;
   Double_t        eleMinNegativeIsoL2;
   Double_t        eleMinPositiveIsoL2;
   Double_t        eleIsoStereoL2;
   Double_t        eleIsoAxialL2;
   Double_t        eleSharedTrkChisq;
   Double_t        eleSharedTrkEcalX;
   Double_t        eleSharedTrkEcalY;
   Double_t        eleMatchChisq;
   Double_t        eleClT;
   Double_t        eleClE;
   Double_t        eleClSeedE;
   Double_t        eleClX;
   Double_t        eleClY;
   Double_t        eleClZ;
   Int_t           eleClHits;
   Int_t           eleClix;
   Int_t           eleCliy;
   Double_t        eleUncorrClT;
   Double_t        eleUncorrClE;
   Double_t        eleUncorrClX;
   Double_t        eleUncorrClY;
   Double_t        eleUncorrClZ;
   Double_t        posPX;
   Double_t        posPY;
   Double_t        posPZ;
   Double_t        posP;
   Double_t        posTrkChisq;
   Int_t           posTrkHits;
   Int_t           posTrkType;
   Double_t        posTrkT;
   Double_t        posTrkTsd;
   Double_t        posTrkZ0;
   Double_t        posTrkLambda;
   Double_t        posTrkD0;
   Double_t        posTrkPhi;
   Double_t        posTrkOmega;
   Double_t        posTrkEcalX;
   Double_t        posTrkEcalY;
   Char_t          posHasL1;
   Char_t          posHasL2;
   Char_t          posHasL3;
   Char_t          posHasL4;
   Char_t          posHasL5;
   Char_t          posHasL6;
   Double_t        posFirstHitX;
   Double_t        posFirstHitY;
   Double_t        posFirstHitT1;
   Double_t        posFirstHitT2;
   Double_t        posFirstHitDEDx1;
   Double_t        posFirstHitDEDx2;
   Int_t           posFirstClusterSize1;
   Int_t           posFirstClusterSize2;
   Int_t           posNHitsShared;
   Double_t        posHitsSharedP;
   Double_t        posLambdaKink1;
   Double_t        posLambdaKink2;
   Double_t        posLambdaKink3;
   Double_t        posPhiKink1;
   Double_t        posPhiKink2;
   Double_t        posPhiKink3;
   Double_t        posIsoStereo;
   Double_t        posIsoAxial;
   Double_t        posMinPositiveIso;
   Double_t        posMinNegativeIso;
   Double_t        posTrkExtrpXL0;
   Double_t        posTrkExtrpYL0;
   Double_t        posTrkExtrpXL1;
   Double_t        posTrkExtrpYL1;
   Double_t        posTrkExtrpXL2;
   Double_t        posTrkExtrpYL2;
   Double_t        posRawMaxAmplL1;
   Double_t        posRawT0L1;
   Double_t        posRawChisqL1;
   Double_t        posRawTDiffL1;
   Double_t        posRawMaxAmplL2;
   Double_t        posRawT0L2;
   Double_t        posRawChisqL2;
   Double_t        posRawTDiffL2;
   Double_t        posRawMaxAmplL3;
   Double_t        posRawT0L3;
   Double_t        posRawChisqL3;
   Double_t        posRawTDiffL3;
   Int_t           posNTrackHits;
   //   Double_t        posHitsSharedP;
   Int_t           posMaxHitsShared;
   Double_t        posMinNegativeIsoL2;
   Double_t        posMinPositiveIsoL2;
   Double_t        posIsoStereoL2;
   Double_t        posIsoAxialL2;
   Double_t        posSharedTrkChisq;
   Double_t        posSharedTrkEcalX;
   Double_t        posSharedTrkEcalY;
   Double_t        posMatchChisq;
   Double_t        posClT;
   Double_t        posClE;
   Double_t        posClSeedE;
   Double_t        posClX;
   Double_t        posClY;
   Double_t        posClZ;
   Int_t           posClHits;
   Int_t           posClix;
   Int_t           posCliy;
   Double_t        posUncorrClT;
   Double_t        posUncorrClE;
   Double_t        posUncorrClX;
   Double_t        posUncorrClY;
   Double_t        posUncorrClZ;
   Double_t        minPositiveIso;
   Double_t        minNegativeIso;
   Double_t        minIso;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_nPos;   //!
   TBranch        *b_nCl;   //!
   TBranch        *b_isCalib;   //!
   TBranch        *b_isPulser;   //!
   TBranch        *b_isSingle0;   //!
   TBranch        *b_isSingle1;   //!
   TBranch        *b_isPair0;   //!
   TBranch        *b_isPair1;   //!
   TBranch        *b_evTime;   //!
   TBranch        *b_evTx;   //!
   TBranch        *b_evTy;   //!
   TBranch        *b_rfT1;   //!
   TBranch        *b_rfT2;   //!
   TBranch        *b_nEcalHits;   //!
   TBranch        *b_nSVTHits;   //!
   TBranch        *b_nEcalCl;   //!
   TBranch        *b_nEcalClele;   //!
   TBranch        *b_nEcalClpos;   //!
   TBranch        *b_nEcalClpho;   //!
   TBranch        *b_nEcalClEleSide;   //!
   TBranch        *b_nEcalClPosSide;   //!
   TBranch        *b_nSVTHitsL1;   //!
   TBranch        *b_nSVTHitsL2;   //!
   TBranch        *b_nSVTHitsL3;   //!
   TBranch        *b_nSVTHitsL4;   //!
   TBranch        *b_nSVTHitsL5;   //!
   TBranch        *b_nSVTHitsL6;   //!
   TBranch        *b_nSVTHitsL1b;   //!
   TBranch        *b_nSVTHitsL2b;   //!
   TBranch        *b_nSVTHitsL3b;   //!
   TBranch        *b_nSVTHitsL4b;   //!
   TBranch        *b_nSVTHitsL5b;   //!
   TBranch        *b_nSVTHitsL6b;   //!
   TBranch        *b_topL1HitX;   //!
   TBranch        *b_topL1HitY;   //!
   TBranch        *b_botL1HitX;   //!
   TBranch        *b_botL1HitY;   //!
   TBranch        *b_uncPX;   //!
   TBranch        *b_uncPY;   //!
   TBranch        *b_uncPZ;   //!
   TBranch        *b_uncP;   //!
   TBranch        *b_uncVX;   //!
   TBranch        *b_uncVY;   //!
   TBranch        *b_uncVZ;   //!
   TBranch        *b_uncChisq;   //!
   TBranch        *b_uncM;   //!
   TBranch        *b_bscPX;   //!
   TBranch        *b_bscPY;   //!
   TBranch        *b_bscPZ;   //!
   TBranch        *b_bscP;   //!
   TBranch        *b_bscVX;   //!
   TBranch        *b_bscVY;   //!
   TBranch        *b_bscVZ;   //!
   TBranch        *b_bscChisq;   //!
   TBranch        *b_bscM;   //!
   TBranch        *b_tarPX;   //!
   TBranch        *b_tarPY;   //!
   TBranch        *b_tarPZ;   //!
   TBranch        *b_tarP;   //!
   TBranch        *b_tarVX;   //!
   TBranch        *b_tarVY;   //!
   TBranch        *b_tarVZ;   //!
   TBranch        *b_tarChisq;   //!
   TBranch        *b_tarM;   //!
   TBranch        *b_vzcPX;   //!
   TBranch        *b_vzcPY;   //!
   TBranch        *b_vzcPZ;   //!
   TBranch        *b_vzcP;   //!
   TBranch        *b_vzcVX;   //!
   TBranch        *b_vzcVY;   //!
   TBranch        *b_vzcVZ;   //!
   TBranch        *b_vzcChisq;   //!
   TBranch        *b_vzcM;   //!
   TBranch        *b_uncCovXX;   //!
   TBranch        *b_uncCovXY;   //!
   TBranch        *b_uncCovXZ;   //!
   TBranch        *b_uncCovYX;   //!
   TBranch        *b_uncCovYY;   //!
   TBranch        *b_uncCovYZ;   //!
   TBranch        *b_uncCovZX;   //!
   TBranch        *b_uncCovZY;   //!
   TBranch        *b_uncCovZZ;   //!
   TBranch        *b_uncElePX;   //!
   TBranch        *b_uncElePY;   //!
   TBranch        *b_uncElePZ;   //!
   TBranch        *b_uncPosPX;   //!
   TBranch        *b_uncPosPY;   //!
   TBranch        *b_uncPosPZ;   //!
   TBranch        *b_uncEleP;   //!
   TBranch        *b_uncPosP;   //!
   TBranch        *b_bscElePX;   //!
   TBranch        *b_bscElePY;   //!
   TBranch        *b_bscElePZ;   //!
   TBranch        *b_bscPosPX;   //!
   TBranch        *b_bscPosPY;   //!
   TBranch        *b_bscPosPZ;   //!
   TBranch        *b_bscEleP;   //!
   TBranch        *b_bscPosP;   //!
   TBranch        *b_tarElePX;   //!
   TBranch        *b_tarElePY;   //!
   TBranch        *b_tarElePZ;   //!
   TBranch        *b_tarPosPX;   //!
   TBranch        *b_tarPosPY;   //!
   TBranch        *b_tarPosPZ;   //!
   TBranch        *b_tarEleP;   //!
   TBranch        *b_tarPosP;   //!
   TBranch        *b_vzcElePX;   //!
   TBranch        *b_vzcElePY;   //!
   TBranch        *b_vzcElePZ;   //!
   TBranch        *b_vzcPosPX;   //!
   TBranch        *b_vzcPosPY;   //!
   TBranch        *b_vzcPosPZ;   //!
   TBranch        *b_vzcEleP;   //!
   TBranch        *b_vzcPosP;   //!
   TBranch        *b_uncEleWtP;   //!
   TBranch        *b_uncPosWtP;   //!
   TBranch        *b_bscEleWtP;   //!
   TBranch        *b_bscPosWtP;   //!
   TBranch        *b_tarEleWtP;   //!
   TBranch        *b_tarPosWtP;   //!
   TBranch        *b_vzcEleWtP;   //!
   TBranch        *b_vzcPosWtP;   //!
   TBranch        *b_uncWtM;   //!
   TBranch        *b_bscWtM;   //!
   TBranch        *b_tarWtM;   //!
   TBranch        *b_vzcWtM;   //!
   TBranch        *b_elePX;   //!
   TBranch        *b_elePY;   //!
   TBranch        *b_elePZ;   //!
   TBranch        *b_eleP;   //!
   TBranch        *b_eleTrkChisq;   //!
   TBranch        *b_eleTrkHits;   //!
   TBranch        *b_eleTrkType;   //!
   TBranch        *b_eleTrkT;   //!
   TBranch        *b_eleTrkTsd;   //!
   TBranch        *b_eleTrkZ0;   //!
   TBranch        *b_eleTrkLambda;   //!
   TBranch        *b_eleTrkD0;   //!
   TBranch        *b_eleTrkPhi;   //!
   TBranch        *b_eleTrkOmega;   //!
   TBranch        *b_eleTrkEcalX;   //!
   TBranch        *b_eleTrkEcalY;   //!
   TBranch        *b_eleHasL1;   //!
   TBranch        *b_eleHasL2;   //!
   TBranch        *b_eleHasL3;   //!
   TBranch        *b_eleHasL4;   //!
   TBranch        *b_eleHasL5;   //!
   TBranch        *b_eleHasL6;   //!
   TBranch        *b_eleFirstHitX;   //!
   TBranch        *b_eleFirstHitY;   //!
   TBranch        *b_eleFirstHitT1;   //!
   TBranch        *b_eleFirstHitT2;   //!
   TBranch        *b_eleFirstHitDEDx1;   //!
   TBranch        *b_eleFirstHitDEDx2;   //!
   TBranch        *b_eleFirstClusterSize1;   //!
   TBranch        *b_eleFirstClusterSize2;   //!
   TBranch        *b_eleNHitsShared;   //!
   //   TBranch        *b_eleHitsSharedP;   //!
   TBranch        *b_eleLambdaKink1;   //!
   TBranch        *b_eleLambdaKink2;   //!
   TBranch        *b_eleLambdaKink3;   //!
   TBranch        *b_elePhiKink1;   //!
   TBranch        *b_elePhiKink2;   //!
   TBranch        *b_elePhiKink3;   //!
   TBranch        *b_eleIsoStereo;   //!
   TBranch        *b_eleIsoAxial;   //!
   TBranch        *b_eleMinPositiveIso;   //!
   TBranch        *b_eleMinNegativeIso;   //!
   TBranch        *b_eleTrkExtrpXL0;   //!
   TBranch        *b_eleTrkExtrpYL0;   //!
   TBranch        *b_eleTrkExtrpXL1;   //!
   TBranch        *b_eleTrkExtrpYL1;   //!
   TBranch        *b_eleTrkExtrpXL2;   //!
   TBranch        *b_eleTrkExtrpYL2;   //!
   TBranch        *b_eleRawMaxAmplL1;   //!
   TBranch        *b_eleRawT0L1;   //!
   TBranch        *b_eleRawChisqL1;   //!
   TBranch        *b_eleRawTDiffL1;   //!
   TBranch        *b_eleRawMaxAmplL2;   //!
   TBranch        *b_eleRawT0L2;   //!
   TBranch        *b_eleRawChisqL2;   //!
   TBranch        *b_eleRawTDiffL2;   //!
   TBranch        *b_eleRawMaxAmplL3;   //!
   TBranch        *b_eleRawT0L3;   //!
   TBranch        *b_eleRawChisqL3;   //!
   TBranch        *b_eleRawTDiffL3;   //!
   TBranch        *b_eleNTrackHits;   //!
   TBranch        *b_eleHitsSharedP;   //!
   TBranch        *b_eleMaxHitsShared;   //!
   TBranch        *b_eleMinNegativeIsoL2;   //!
   TBranch        *b_eleMinPositiveIsoL2;   //!
   TBranch        *b_eleIsoStereoL2;   //!
   TBranch        *b_eleIsoAxialL2;   //!
   TBranch        *b_eleSharedTrkChisq;   //!
   TBranch        *b_eleSharedTrkEcalX;   //!
   TBranch        *b_eleSharedTrkEcalY;   //!
   TBranch        *b_eleMatchChisq;   //!
   TBranch        *b_eleClT;   //!
   TBranch        *b_eleClE;   //!
   TBranch        *b_eleClSeedE;   //!
   TBranch        *b_eleClX;   //!
   TBranch        *b_eleClY;   //!
   TBranch        *b_eleClZ;   //!
   TBranch        *b_eleClHits;   //!
   TBranch        *b_eleClix;   //!
   TBranch        *b_eleCliy;   //!
   TBranch        *b_eleUncorrClT;   //!
   TBranch        *b_eleUncorrClE;   //!
   TBranch        *b_eleUncorrClX;   //!
   TBranch        *b_eleUncorrClY;   //!
   TBranch        *b_eleUncorrClZ;   //!
   TBranch        *b_posPX;   //!
   TBranch        *b_posPY;   //!
   TBranch        *b_posPZ;   //!
   TBranch        *b_posP;   //!
   TBranch        *b_posTrkChisq;   //!
   TBranch        *b_posTrkHits;   //!
   TBranch        *b_posTrkType;   //!
   TBranch        *b_posTrkT;   //!
   TBranch        *b_posTrkTsd;   //!
   TBranch        *b_posTrkZ0;   //!
   TBranch        *b_posTrkLambda;   //!
   TBranch        *b_posTrkD0;   //!
   TBranch        *b_posTrkPhi;   //!
   TBranch        *b_posTrkOmega;   //!
   TBranch        *b_posTrkEcalX;   //!
   TBranch        *b_posTrkEcalY;   //!
   TBranch        *b_posHasL1;   //!
   TBranch        *b_posHasL2;   //!
   TBranch        *b_posHasL3;   //!
   TBranch        *b_posHasL4;   //!
   TBranch        *b_posHasL5;   //!
   TBranch        *b_posHasL6;   //!
   TBranch        *b_posFirstHitX;   //!
   TBranch        *b_posFirstHitY;   //!
   TBranch        *b_posFirstHitT1;   //!
   TBranch        *b_posFirstHitT2;   //!
   TBranch        *b_posFirstHitDEDx1;   //!
   TBranch        *b_posFirstHitDEDx2;   //!
   TBranch        *b_posFirstClusterSize1;   //!
   TBranch        *b_posFirstClusterSize2;   //!
   TBranch        *b_posNHitsShared;   //!
   //   TBranch        *b_posHitsSharedP;   //!
   TBranch        *b_posLambdaKink1;   //!
   TBranch        *b_posLambdaKink2;   //!
   TBranch        *b_posLambdaKink3;   //!
   TBranch        *b_posPhiKink1;   //!
   TBranch        *b_posPhiKink2;   //!
   TBranch        *b_posPhiKink3;   //!
   TBranch        *b_posIsoStereo;   //!
   TBranch        *b_posIsoAxial;   //!
   TBranch        *b_posMinPositiveIso;   //!
   TBranch        *b_posMinNegativeIso;   //!
   TBranch        *b_posTrkExtrpXL0;   //!
   TBranch        *b_posTrkExtrpYL0;   //!
   TBranch        *b_posTrkExtrpXL1;   //!
   TBranch        *b_posTrkExtrpYL1;   //!
   TBranch        *b_posTrkExtrpXL2;   //!
   TBranch        *b_posTrkExtrpYL2;   //!
   TBranch        *b_posRawMaxAmplL1;   //!
   TBranch        *b_posRawT0L1;   //!
   TBranch        *b_posRawChisqL1;   //!
   TBranch        *b_posRawTDiffL1;   //!
   TBranch        *b_posRawMaxAmplL2;   //!
   TBranch        *b_posRawT0L2;   //!
   TBranch        *b_posRawChisqL2;   //!
   TBranch        *b_posRawTDiffL2;   //!
   TBranch        *b_posRawMaxAmplL3;   //!
   TBranch        *b_posRawT0L3;   //!
   TBranch        *b_posRawChisqL3;   //!
   TBranch        *b_posRawTDiffL3;   //!
   TBranch        *b_posNTrackHits;   //!
   TBranch        *b_posHitsSharedP;   //!
   TBranch        *b_posMaxHitsShared;   //!
   TBranch        *b_posMinNegativeIsoL2;   //!
   TBranch        *b_posMinPositiveIsoL2;   //!
   TBranch        *b_posIsoStereoL2;   //!
   TBranch        *b_posIsoAxialL2;   //!
   TBranch        *b_posSharedTrkChisq;   //!
   TBranch        *b_posSharedTrkEcalX;   //!
   TBranch        *b_posSharedTrkEcalY;   //!
   TBranch        *b_posMatchChisq;   //!
   TBranch        *b_posClT;   //!
   TBranch        *b_posClE;   //!
   TBranch        *b_posClSeedE;   //!
   TBranch        *b_posClX;   //!
   TBranch        *b_posClY;   //!
   TBranch        *b_posClZ;   //!
   TBranch        *b_posClHits;   //!
   TBranch        *b_posClix;   //!
   TBranch        *b_posCliy;   //!
   TBranch        *b_posUncorrClT;   //!
   TBranch        *b_posUncorrClE;   //!
   TBranch        *b_posUncorrClX;   //!
   TBranch        *b_posUncorrClY;   //!
   TBranch        *b_posUncorrClZ;   //!
   TBranch        *b_minPositiveIso;   //!
   TBranch        *b_minNegativeIso;   //!
   TBranch        *b_minIso;   //!

   Event_Selection(TTree *tree=0);
   virtual ~Event_Selection();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Event_Selection_cxx
Event_Selection::Event_Selection(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("Event_Selection",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Event_Selection","");
      chain->Add("../Data/hps_007796_nt_tri_3.11.1.root/ntuple");
      //chain->Add("../Data/wab-WBT.root/ntuple");
      //chain->Add("../Data/tritrig-WBT.root/ntuple");
      //chain->Add("../Data/RAD-WBT.root/ntuple");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Event_Selection::~Event_Selection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Event_Selection::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Event_Selection::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Event_Selection::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("nPos", &nPos, &b_nPos);
   fChain->SetBranchAddress("nCl", &nCl, &b_nCl);
   fChain->SetBranchAddress("isCalib", &isCalib, &b_isCalib);
   fChain->SetBranchAddress("isPulser", &isPulser, &b_isPulser);
   fChain->SetBranchAddress("isSingle0", &isSingle0, &b_isSingle0);
   fChain->SetBranchAddress("isSingle1", &isSingle1, &b_isSingle1);
   fChain->SetBranchAddress("isPair0", &isPair0, &b_isPair0);
   fChain->SetBranchAddress("isPair1", &isPair1, &b_isPair1);
   fChain->SetBranchAddress("evTime", &evTime, &b_evTime);
   fChain->SetBranchAddress("evTx", &evTx, &b_evTx);
   fChain->SetBranchAddress("evTy", &evTy, &b_evTy);
   fChain->SetBranchAddress("rfT1", &rfT1, &b_rfT1);
   fChain->SetBranchAddress("rfT2", &rfT2, &b_rfT2);
   fChain->SetBranchAddress("nEcalHits", &nEcalHits, &b_nEcalHits);
   fChain->SetBranchAddress("nSVTHits", &nSVTHits, &b_nSVTHits);
   fChain->SetBranchAddress("nEcalCl", &nEcalCl, &b_nEcalCl);
   fChain->SetBranchAddress("nEcalClele", &nEcalClele, &b_nEcalClele);
   fChain->SetBranchAddress("nEcalClpos", &nEcalClpos, &b_nEcalClpos);
   fChain->SetBranchAddress("nEcalClpho", &nEcalClpho, &b_nEcalClpho);
   fChain->SetBranchAddress("nEcalClEleSide", &nEcalClEleSide, &b_nEcalClEleSide);
   fChain->SetBranchAddress("nEcalClPosSide", &nEcalClPosSide, &b_nEcalClPosSide);
   fChain->SetBranchAddress("nSVTHitsL1", &nSVTHitsL1, &b_nSVTHitsL1);
   fChain->SetBranchAddress("nSVTHitsL2", &nSVTHitsL2, &b_nSVTHitsL2);
   fChain->SetBranchAddress("nSVTHitsL3", &nSVTHitsL3, &b_nSVTHitsL3);
   fChain->SetBranchAddress("nSVTHitsL4", &nSVTHitsL4, &b_nSVTHitsL4);
   fChain->SetBranchAddress("nSVTHitsL5", &nSVTHitsL5, &b_nSVTHitsL5);
   fChain->SetBranchAddress("nSVTHitsL6", &nSVTHitsL6, &b_nSVTHitsL6);
   fChain->SetBranchAddress("nSVTHitsL1b", &nSVTHitsL1b, &b_nSVTHitsL1b);
   fChain->SetBranchAddress("nSVTHitsL2b", &nSVTHitsL2b, &b_nSVTHitsL2b);
   fChain->SetBranchAddress("nSVTHitsL3b", &nSVTHitsL3b, &b_nSVTHitsL3b);
   fChain->SetBranchAddress("nSVTHitsL4b", &nSVTHitsL4b, &b_nSVTHitsL4b);
   fChain->SetBranchAddress("nSVTHitsL5b", &nSVTHitsL5b, &b_nSVTHitsL5b);
   fChain->SetBranchAddress("nSVTHitsL6b", &nSVTHitsL6b, &b_nSVTHitsL6b);
   fChain->SetBranchAddress("topL1HitX", &topL1HitX, &b_topL1HitX);
   fChain->SetBranchAddress("topL1HitY", &topL1HitY, &b_topL1HitY);
   fChain->SetBranchAddress("botL1HitX", &botL1HitX, &b_botL1HitX);
   fChain->SetBranchAddress("botL1HitY", &botL1HitY, &b_botL1HitY);
   fChain->SetBranchAddress("uncPX", &uncPX, &b_uncPX);
   fChain->SetBranchAddress("uncPY", &uncPY, &b_uncPY);
   fChain->SetBranchAddress("uncPZ", &uncPZ, &b_uncPZ);
   fChain->SetBranchAddress("uncP", &uncP, &b_uncP);
   fChain->SetBranchAddress("uncVX", &uncVX, &b_uncVX);
   fChain->SetBranchAddress("uncVY", &uncVY, &b_uncVY);
   fChain->SetBranchAddress("uncVZ", &uncVZ, &b_uncVZ);
   fChain->SetBranchAddress("uncChisq", &uncChisq, &b_uncChisq);
   fChain->SetBranchAddress("uncM", &uncM, &b_uncM);
   fChain->SetBranchAddress("bscPX", &bscPX, &b_bscPX);
   fChain->SetBranchAddress("bscPY", &bscPY, &b_bscPY);
   fChain->SetBranchAddress("bscPZ", &bscPZ, &b_bscPZ);
   fChain->SetBranchAddress("bscP", &bscP, &b_bscP);
   fChain->SetBranchAddress("bscVX", &bscVX, &b_bscVX);
   fChain->SetBranchAddress("bscVY", &bscVY, &b_bscVY);
   fChain->SetBranchAddress("bscVZ", &bscVZ, &b_bscVZ);
   fChain->SetBranchAddress("bscChisq", &bscChisq, &b_bscChisq);
   fChain->SetBranchAddress("bscM", &bscM, &b_bscM);
   fChain->SetBranchAddress("tarPX", &tarPX, &b_tarPX);
   fChain->SetBranchAddress("tarPY", &tarPY, &b_tarPY);
   fChain->SetBranchAddress("tarPZ", &tarPZ, &b_tarPZ);
   fChain->SetBranchAddress("tarP", &tarP, &b_tarP);
   fChain->SetBranchAddress("tarVX", &tarVX, &b_tarVX);
   fChain->SetBranchAddress("tarVY", &tarVY, &b_tarVY);
   fChain->SetBranchAddress("tarVZ", &tarVZ, &b_tarVZ);
   fChain->SetBranchAddress("tarChisq", &tarChisq, &b_tarChisq);
   fChain->SetBranchAddress("tarM", &tarM, &b_tarM);
   fChain->SetBranchAddress("vzcPX", &vzcPX, &b_vzcPX);
   fChain->SetBranchAddress("vzcPY", &vzcPY, &b_vzcPY);
   fChain->SetBranchAddress("vzcPZ", &vzcPZ, &b_vzcPZ);
   fChain->SetBranchAddress("vzcP", &vzcP, &b_vzcP);
   fChain->SetBranchAddress("vzcVX", &vzcVX, &b_vzcVX);
   fChain->SetBranchAddress("vzcVY", &vzcVY, &b_vzcVY);
   fChain->SetBranchAddress("vzcVZ", &vzcVZ, &b_vzcVZ);
   fChain->SetBranchAddress("vzcChisq", &vzcChisq, &b_vzcChisq);
   fChain->SetBranchAddress("vzcM", &vzcM, &b_vzcM);
   fChain->SetBranchAddress("uncCovXX", &uncCovXX, &b_uncCovXX);
   fChain->SetBranchAddress("uncCovXY", &uncCovXY, &b_uncCovXY);
   fChain->SetBranchAddress("uncCovXZ", &uncCovXZ, &b_uncCovXZ);
   fChain->SetBranchAddress("uncCovYX", &uncCovYX, &b_uncCovYX);
   fChain->SetBranchAddress("uncCovYY", &uncCovYY, &b_uncCovYY);
   fChain->SetBranchAddress("uncCovYZ", &uncCovYZ, &b_uncCovYZ);
   fChain->SetBranchAddress("uncCovZX", &uncCovZX, &b_uncCovZX);
   fChain->SetBranchAddress("uncCovZY", &uncCovZY, &b_uncCovZY);
   fChain->SetBranchAddress("uncCovZZ", &uncCovZZ, &b_uncCovZZ);
   fChain->SetBranchAddress("uncElePX", &uncElePX, &b_uncElePX);
   fChain->SetBranchAddress("uncElePY", &uncElePY, &b_uncElePY);
   fChain->SetBranchAddress("uncElePZ", &uncElePZ, &b_uncElePZ);
   fChain->SetBranchAddress("uncPosPX", &uncPosPX, &b_uncPosPX);
   fChain->SetBranchAddress("uncPosPY", &uncPosPY, &b_uncPosPY);
   fChain->SetBranchAddress("uncPosPZ", &uncPosPZ, &b_uncPosPZ);
   fChain->SetBranchAddress("uncEleP", &uncEleP, &b_uncEleP);
   fChain->SetBranchAddress("uncPosP", &uncPosP, &b_uncPosP);
   fChain->SetBranchAddress("bscElePX", &bscElePX, &b_bscElePX);
   fChain->SetBranchAddress("bscElePY", &bscElePY, &b_bscElePY);
   fChain->SetBranchAddress("bscElePZ", &bscElePZ, &b_bscElePZ);
   fChain->SetBranchAddress("bscPosPX", &bscPosPX, &b_bscPosPX);
   fChain->SetBranchAddress("bscPosPY", &bscPosPY, &b_bscPosPY);
   fChain->SetBranchAddress("bscPosPZ", &bscPosPZ, &b_bscPosPZ);
   fChain->SetBranchAddress("bscEleP", &bscEleP, &b_bscEleP);
   fChain->SetBranchAddress("bscPosP", &bscPosP, &b_bscPosP);
   fChain->SetBranchAddress("tarElePX", &tarElePX, &b_tarElePX);
   fChain->SetBranchAddress("tarElePY", &tarElePY, &b_tarElePY);
   fChain->SetBranchAddress("tarElePZ", &tarElePZ, &b_tarElePZ);
   fChain->SetBranchAddress("tarPosPX", &tarPosPX, &b_tarPosPX);
   fChain->SetBranchAddress("tarPosPY", &tarPosPY, &b_tarPosPY);
   fChain->SetBranchAddress("tarPosPZ", &tarPosPZ, &b_tarPosPZ);
   fChain->SetBranchAddress("tarEleP", &tarEleP, &b_tarEleP);
   fChain->SetBranchAddress("tarPosP", &tarPosP, &b_tarPosP);
   fChain->SetBranchAddress("vzcElePX", &vzcElePX, &b_vzcElePX);
   fChain->SetBranchAddress("vzcElePY", &vzcElePY, &b_vzcElePY);
   fChain->SetBranchAddress("vzcElePZ", &vzcElePZ, &b_vzcElePZ);
   fChain->SetBranchAddress("vzcPosPX", &vzcPosPX, &b_vzcPosPX);
   fChain->SetBranchAddress("vzcPosPY", &vzcPosPY, &b_vzcPosPY);
   fChain->SetBranchAddress("vzcPosPZ", &vzcPosPZ, &b_vzcPosPZ);
   fChain->SetBranchAddress("vzcEleP", &vzcEleP, &b_vzcEleP);
   fChain->SetBranchAddress("vzcPosP", &vzcPosP, &b_vzcPosP);
   fChain->SetBranchAddress("uncEleWtP", &uncEleWtP, &b_uncEleWtP);
   fChain->SetBranchAddress("uncPosWtP", &uncPosWtP, &b_uncPosWtP);
   fChain->SetBranchAddress("bscEleWtP", &bscEleWtP, &b_bscEleWtP);
   fChain->SetBranchAddress("bscPosWtP", &bscPosWtP, &b_bscPosWtP);
   fChain->SetBranchAddress("tarEleWtP", &tarEleWtP, &b_tarEleWtP);
   fChain->SetBranchAddress("tarPosWtP", &tarPosWtP, &b_tarPosWtP);
   fChain->SetBranchAddress("vzcEleWtP", &vzcEleWtP, &b_vzcEleWtP);
   fChain->SetBranchAddress("vzcPosWtP", &vzcPosWtP, &b_vzcPosWtP);
   fChain->SetBranchAddress("uncWtM", &uncWtM, &b_uncWtM);
   fChain->SetBranchAddress("bscWtM", &bscWtM, &b_bscWtM);
   fChain->SetBranchAddress("tarWtM", &tarWtM, &b_tarWtM);
   fChain->SetBranchAddress("vzcWtM", &vzcWtM, &b_vzcWtM);
   fChain->SetBranchAddress("elePX", &elePX, &b_elePX);
   fChain->SetBranchAddress("elePY", &elePY, &b_elePY);
   fChain->SetBranchAddress("elePZ", &elePZ, &b_elePZ);
   fChain->SetBranchAddress("eleP", &eleP, &b_eleP);
   fChain->SetBranchAddress("eleTrkChisq", &eleTrkChisq, &b_eleTrkChisq);
   fChain->SetBranchAddress("eleTrkHits", &eleTrkHits, &b_eleTrkHits);
   fChain->SetBranchAddress("eleTrkType", &eleTrkType, &b_eleTrkType);
   fChain->SetBranchAddress("eleTrkT", &eleTrkT, &b_eleTrkT);
   fChain->SetBranchAddress("eleTrkTsd", &eleTrkTsd, &b_eleTrkTsd);
   fChain->SetBranchAddress("eleTrkZ0", &eleTrkZ0, &b_eleTrkZ0);
   fChain->SetBranchAddress("eleTrkLambda", &eleTrkLambda, &b_eleTrkLambda);
   fChain->SetBranchAddress("eleTrkD0", &eleTrkD0, &b_eleTrkD0);
   fChain->SetBranchAddress("eleTrkPhi", &eleTrkPhi, &b_eleTrkPhi);
   fChain->SetBranchAddress("eleTrkOmega", &eleTrkOmega, &b_eleTrkOmega);
   fChain->SetBranchAddress("eleTrkEcalX", &eleTrkEcalX, &b_eleTrkEcalX);
   fChain->SetBranchAddress("eleTrkEcalY", &eleTrkEcalY, &b_eleTrkEcalY);
   fChain->SetBranchAddress("eleHasL1", &eleHasL1, &b_eleHasL1);
   fChain->SetBranchAddress("eleHasL2", &eleHasL2, &b_eleHasL2);
   fChain->SetBranchAddress("eleHasL3", &eleHasL3, &b_eleHasL3);
   fChain->SetBranchAddress("eleHasL4", &eleHasL4, &b_eleHasL4);
   fChain->SetBranchAddress("eleHasL5", &eleHasL5, &b_eleHasL5);
   fChain->SetBranchAddress("eleHasL6", &eleHasL6, &b_eleHasL6);
   fChain->SetBranchAddress("eleFirstHitX", &eleFirstHitX, &b_eleFirstHitX);
   fChain->SetBranchAddress("eleFirstHitY", &eleFirstHitY, &b_eleFirstHitY);
   fChain->SetBranchAddress("eleFirstHitT1", &eleFirstHitT1, &b_eleFirstHitT1);
   fChain->SetBranchAddress("eleFirstHitT2", &eleFirstHitT2, &b_eleFirstHitT2);
   fChain->SetBranchAddress("eleFirstHitDEDx1", &eleFirstHitDEDx1, &b_eleFirstHitDEDx1);
   fChain->SetBranchAddress("eleFirstHitDEDx2", &eleFirstHitDEDx2, &b_eleFirstHitDEDx2);
   fChain->SetBranchAddress("eleFirstClusterSize1", &eleFirstClusterSize1, &b_eleFirstClusterSize1);
   fChain->SetBranchAddress("eleFirstClusterSize2", &eleFirstClusterSize2, &b_eleFirstClusterSize2);
   fChain->SetBranchAddress("eleNHitsShared", &eleNHitsShared, &b_eleNHitsShared);
   fChain->SetBranchAddress("eleHitsSharedP", &eleHitsSharedP, &b_eleHitsSharedP);
   fChain->SetBranchAddress("eleLambdaKink1", &eleLambdaKink1, &b_eleLambdaKink1);
   fChain->SetBranchAddress("eleLambdaKink2", &eleLambdaKink2, &b_eleLambdaKink2);
   fChain->SetBranchAddress("eleLambdaKink3", &eleLambdaKink3, &b_eleLambdaKink3);
   fChain->SetBranchAddress("elePhiKink1", &elePhiKink1, &b_elePhiKink1);
   fChain->SetBranchAddress("elePhiKink2", &elePhiKink2, &b_elePhiKink2);
   fChain->SetBranchAddress("elePhiKink3", &elePhiKink3, &b_elePhiKink3);
   fChain->SetBranchAddress("eleIsoStereo", &eleIsoStereo, &b_eleIsoStereo);
   fChain->SetBranchAddress("eleIsoAxial", &eleIsoAxial, &b_eleIsoAxial);
   fChain->SetBranchAddress("eleMinPositiveIso", &eleMinPositiveIso, &b_eleMinPositiveIso);
   fChain->SetBranchAddress("eleMinNegativeIso", &eleMinNegativeIso, &b_eleMinNegativeIso);
   fChain->SetBranchAddress("eleTrkExtrpXL0", &eleTrkExtrpXL0, &b_eleTrkExtrpXL0);
   fChain->SetBranchAddress("eleTrkExtrpYL0", &eleTrkExtrpYL0, &b_eleTrkExtrpYL0);
   fChain->SetBranchAddress("eleTrkExtrpXL1", &eleTrkExtrpXL1, &b_eleTrkExtrpXL1);
   fChain->SetBranchAddress("eleTrkExtrpYL1", &eleTrkExtrpYL1, &b_eleTrkExtrpYL1);
   fChain->SetBranchAddress("eleTrkExtrpXL2", &eleTrkExtrpXL2, &b_eleTrkExtrpXL2);
   fChain->SetBranchAddress("eleTrkExtrpYL2", &eleTrkExtrpYL2, &b_eleTrkExtrpYL2);
   fChain->SetBranchAddress("eleRawMaxAmplL1", &eleRawMaxAmplL1, &b_eleRawMaxAmplL1);
   fChain->SetBranchAddress("eleRawT0L1", &eleRawT0L1, &b_eleRawT0L1);
   fChain->SetBranchAddress("eleRawChisqL1", &eleRawChisqL1, &b_eleRawChisqL1);
   fChain->SetBranchAddress("eleRawTDiffL1", &eleRawTDiffL1, &b_eleRawTDiffL1);
   fChain->SetBranchAddress("eleRawMaxAmplL2", &eleRawMaxAmplL2, &b_eleRawMaxAmplL2);
   fChain->SetBranchAddress("eleRawT0L2", &eleRawT0L2, &b_eleRawT0L2);
   fChain->SetBranchAddress("eleRawChisqL2", &eleRawChisqL2, &b_eleRawChisqL2);
   fChain->SetBranchAddress("eleRawTDiffL2", &eleRawTDiffL2, &b_eleRawTDiffL2);
   fChain->SetBranchAddress("eleRawMaxAmplL3", &eleRawMaxAmplL3, &b_eleRawMaxAmplL3);
   fChain->SetBranchAddress("eleRawT0L3", &eleRawT0L3, &b_eleRawT0L3);
   fChain->SetBranchAddress("eleRawChisqL3", &eleRawChisqL3, &b_eleRawChisqL3);
   fChain->SetBranchAddress("eleRawTDiffL3", &eleRawTDiffL3, &b_eleRawTDiffL3);
   fChain->SetBranchAddress("eleNTrackHits", &eleNTrackHits, &b_eleNTrackHits);
//    fChain->SetBranchAddress("eleHitsSharedP", &eleHitsSharedP, &b_eleHitsSharedP);
   fChain->SetBranchAddress("eleMaxHitsShared", &eleMaxHitsShared, &b_eleMaxHitsShared);
   fChain->SetBranchAddress("eleMinNegativeIsoL2", &eleMinNegativeIsoL2, &b_eleMinNegativeIsoL2);
   fChain->SetBranchAddress("eleMinPositiveIsoL2", &eleMinPositiveIsoL2, &b_eleMinPositiveIsoL2);
   fChain->SetBranchAddress("eleIsoStereoL2", &eleIsoStereoL2, &b_eleIsoStereoL2);
   fChain->SetBranchAddress("eleIsoAxialL2", &eleIsoAxialL2, &b_eleIsoAxialL2);
   fChain->SetBranchAddress("eleSharedTrkChisq", &eleSharedTrkChisq, &b_eleSharedTrkChisq);
   fChain->SetBranchAddress("eleSharedTrkEcalX", &eleSharedTrkEcalX, &b_eleSharedTrkEcalX);
   fChain->SetBranchAddress("eleSharedTrkEcalY", &eleSharedTrkEcalY, &b_eleSharedTrkEcalY);
   fChain->SetBranchAddress("eleMatchChisq", &eleMatchChisq, &b_eleMatchChisq);
   fChain->SetBranchAddress("eleClT", &eleClT, &b_eleClT);
   fChain->SetBranchAddress("eleClE", &eleClE, &b_eleClE);
   fChain->SetBranchAddress("eleClSeedE", &eleClSeedE, &b_eleClSeedE);
   fChain->SetBranchAddress("eleClX", &eleClX, &b_eleClX);
   fChain->SetBranchAddress("eleClY", &eleClY, &b_eleClY);
   fChain->SetBranchAddress("eleClZ", &eleClZ, &b_eleClZ);
   fChain->SetBranchAddress("eleClHits", &eleClHits, &b_eleClHits);
   fChain->SetBranchAddress("eleClix", &eleClix, &b_eleClix);
   fChain->SetBranchAddress("eleCliy", &eleCliy, &b_eleCliy);
   fChain->SetBranchAddress("eleUncorrClT", &eleUncorrClT, &b_eleUncorrClT);
   fChain->SetBranchAddress("eleUncorrClE", &eleUncorrClE, &b_eleUncorrClE);
   fChain->SetBranchAddress("eleUncorrClX", &eleUncorrClX, &b_eleUncorrClX);
   fChain->SetBranchAddress("eleUncorrClY", &eleUncorrClY, &b_eleUncorrClY);
   fChain->SetBranchAddress("eleUncorrClZ", &eleUncorrClZ, &b_eleUncorrClZ);
   fChain->SetBranchAddress("posPX", &posPX, &b_posPX);
   fChain->SetBranchAddress("posPY", &posPY, &b_posPY);
   fChain->SetBranchAddress("posPZ", &posPZ, &b_posPZ);
   fChain->SetBranchAddress("posP", &posP, &b_posP);
   fChain->SetBranchAddress("posTrkChisq", &posTrkChisq, &b_posTrkChisq);
   fChain->SetBranchAddress("posTrkHits", &posTrkHits, &b_posTrkHits);
   fChain->SetBranchAddress("posTrkType", &posTrkType, &b_posTrkType);
   fChain->SetBranchAddress("posTrkT", &posTrkT, &b_posTrkT);
   fChain->SetBranchAddress("posTrkTsd", &posTrkTsd, &b_posTrkTsd);
   fChain->SetBranchAddress("posTrkZ0", &posTrkZ0, &b_posTrkZ0);
   fChain->SetBranchAddress("posTrkLambda", &posTrkLambda, &b_posTrkLambda);
   fChain->SetBranchAddress("posTrkD0", &posTrkD0, &b_posTrkD0);
   fChain->SetBranchAddress("posTrkPhi", &posTrkPhi, &b_posTrkPhi);
   fChain->SetBranchAddress("posTrkOmega", &posTrkOmega, &b_posTrkOmega);
   fChain->SetBranchAddress("posTrkEcalX", &posTrkEcalX, &b_posTrkEcalX);
   fChain->SetBranchAddress("posTrkEcalY", &posTrkEcalY, &b_posTrkEcalY);
   fChain->SetBranchAddress("posHasL1", &posHasL1, &b_posHasL1);
   fChain->SetBranchAddress("posHasL2", &posHasL2, &b_posHasL2);
   fChain->SetBranchAddress("posHasL3", &posHasL3, &b_posHasL3);
   fChain->SetBranchAddress("posHasL4", &posHasL4, &b_posHasL4);
   fChain->SetBranchAddress("posHasL5", &posHasL5, &b_posHasL5);
   fChain->SetBranchAddress("posHasL6", &posHasL6, &b_posHasL6);
   fChain->SetBranchAddress("posFirstHitX", &posFirstHitX, &b_posFirstHitX);
   fChain->SetBranchAddress("posFirstHitY", &posFirstHitY, &b_posFirstHitY);
   fChain->SetBranchAddress("posFirstHitT1", &posFirstHitT1, &b_posFirstHitT1);
   fChain->SetBranchAddress("posFirstHitT2", &posFirstHitT2, &b_posFirstHitT2);
   fChain->SetBranchAddress("posFirstHitDEDx1", &posFirstHitDEDx1, &b_posFirstHitDEDx1);
   fChain->SetBranchAddress("posFirstHitDEDx2", &posFirstHitDEDx2, &b_posFirstHitDEDx2);
   fChain->SetBranchAddress("posFirstClusterSize1", &posFirstClusterSize1, &b_posFirstClusterSize1);
   fChain->SetBranchAddress("posFirstClusterSize2", &posFirstClusterSize2, &b_posFirstClusterSize2);
   fChain->SetBranchAddress("posNHitsShared", &posNHitsShared, &b_posNHitsShared);
   fChain->SetBranchAddress("posHitsSharedP", &posHitsSharedP, &b_posHitsSharedP);
   fChain->SetBranchAddress("posLambdaKink1", &posLambdaKink1, &b_posLambdaKink1);
   fChain->SetBranchAddress("posLambdaKink2", &posLambdaKink2, &b_posLambdaKink2);
   fChain->SetBranchAddress("posLambdaKink3", &posLambdaKink3, &b_posLambdaKink3);
   fChain->SetBranchAddress("posPhiKink1", &posPhiKink1, &b_posPhiKink1);
   fChain->SetBranchAddress("posPhiKink2", &posPhiKink2, &b_posPhiKink2);
   fChain->SetBranchAddress("posPhiKink3", &posPhiKink3, &b_posPhiKink3);
   fChain->SetBranchAddress("posIsoStereo", &posIsoStereo, &b_posIsoStereo);
   fChain->SetBranchAddress("posIsoAxial", &posIsoAxial, &b_posIsoAxial);
   fChain->SetBranchAddress("posMinPositiveIso", &posMinPositiveIso, &b_posMinPositiveIso);
   fChain->SetBranchAddress("posMinNegativeIso", &posMinNegativeIso, &b_posMinNegativeIso);
   fChain->SetBranchAddress("posTrkExtrpXL0", &posTrkExtrpXL0, &b_posTrkExtrpXL0);
   fChain->SetBranchAddress("posTrkExtrpYL0", &posTrkExtrpYL0, &b_posTrkExtrpYL0);
   fChain->SetBranchAddress("posTrkExtrpXL1", &posTrkExtrpXL1, &b_posTrkExtrpXL1);
   fChain->SetBranchAddress("posTrkExtrpYL1", &posTrkExtrpYL1, &b_posTrkExtrpYL1);
   fChain->SetBranchAddress("posTrkExtrpXL2", &posTrkExtrpXL2, &b_posTrkExtrpXL2);
   fChain->SetBranchAddress("posTrkExtrpYL2", &posTrkExtrpYL2, &b_posTrkExtrpYL2);
   fChain->SetBranchAddress("posRawMaxAmplL1", &posRawMaxAmplL1, &b_posRawMaxAmplL1);
   fChain->SetBranchAddress("posRawT0L1", &posRawT0L1, &b_posRawT0L1);
   fChain->SetBranchAddress("posRawChisqL1", &posRawChisqL1, &b_posRawChisqL1);
   fChain->SetBranchAddress("posRawTDiffL1", &posRawTDiffL1, &b_posRawTDiffL1);
   fChain->SetBranchAddress("posRawMaxAmplL2", &posRawMaxAmplL2, &b_posRawMaxAmplL2);
   fChain->SetBranchAddress("posRawT0L2", &posRawT0L2, &b_posRawT0L2);
   fChain->SetBranchAddress("posRawChisqL2", &posRawChisqL2, &b_posRawChisqL2);
   fChain->SetBranchAddress("posRawTDiffL2", &posRawTDiffL2, &b_posRawTDiffL2);
   fChain->SetBranchAddress("posRawMaxAmplL3", &posRawMaxAmplL3, &b_posRawMaxAmplL3);
   fChain->SetBranchAddress("posRawT0L3", &posRawT0L3, &b_posRawT0L3);
   fChain->SetBranchAddress("posRawChisqL3", &posRawChisqL3, &b_posRawChisqL3);
   fChain->SetBranchAddress("posRawTDiffL3", &posRawTDiffL3, &b_posRawTDiffL3);
   fChain->SetBranchAddress("posNTrackHits", &posNTrackHits, &b_posNTrackHits);
//    fChain->SetBranchAddress("posHitsSharedP", &posHitsSharedP, &b_posHitsSharedP);
   fChain->SetBranchAddress("posMaxHitsShared", &posMaxHitsShared, &b_posMaxHitsShared);
   fChain->SetBranchAddress("posMinNegativeIsoL2", &posMinNegativeIsoL2, &b_posMinNegativeIsoL2);
   fChain->SetBranchAddress("posMinPositiveIsoL2", &posMinPositiveIsoL2, &b_posMinPositiveIsoL2);
   fChain->SetBranchAddress("posIsoStereoL2", &posIsoStereoL2, &b_posIsoStereoL2);
   fChain->SetBranchAddress("posIsoAxialL2", &posIsoAxialL2, &b_posIsoAxialL2);
   fChain->SetBranchAddress("posSharedTrkChisq", &posSharedTrkChisq, &b_posSharedTrkChisq);
   fChain->SetBranchAddress("posSharedTrkEcalX", &posSharedTrkEcalX, &b_posSharedTrkEcalX);
   fChain->SetBranchAddress("posSharedTrkEcalY", &posSharedTrkEcalY, &b_posSharedTrkEcalY);
   fChain->SetBranchAddress("posMatchChisq", &posMatchChisq, &b_posMatchChisq);
   fChain->SetBranchAddress("posClT", &posClT, &b_posClT);
   fChain->SetBranchAddress("posClE", &posClE, &b_posClE);
   fChain->SetBranchAddress("posClSeedE", &posClSeedE, &b_posClSeedE);
   fChain->SetBranchAddress("posClX", &posClX, &b_posClX);
   fChain->SetBranchAddress("posClY", &posClY, &b_posClY);
   fChain->SetBranchAddress("posClZ", &posClZ, &b_posClZ);
   fChain->SetBranchAddress("posClHits", &posClHits, &b_posClHits);
   fChain->SetBranchAddress("posClix", &posClix, &b_posClix);
   fChain->SetBranchAddress("posCliy", &posCliy, &b_posCliy);
   fChain->SetBranchAddress("posUncorrClT", &posUncorrClT, &b_posUncorrClT);
   fChain->SetBranchAddress("posUncorrClE", &posUncorrClE, &b_posUncorrClE);
   fChain->SetBranchAddress("posUncorrClX", &posUncorrClX, &b_posUncorrClX);
   fChain->SetBranchAddress("posUncorrClY", &posUncorrClY, &b_posUncorrClY);
   fChain->SetBranchAddress("posUncorrClZ", &posUncorrClZ, &b_posUncorrClZ);
   fChain->SetBranchAddress("minPositiveIso", &minPositiveIso, &b_minPositiveIso);
   fChain->SetBranchAddress("minNegativeIso", &minNegativeIso, &b_minNegativeIso);
   fChain->SetBranchAddress("minIso", &minIso, &b_minIso);
   Notify();
}

Bool_t Event_Selection::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Event_Selection::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Event_Selection::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Event_Selection_cxx
