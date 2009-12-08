!
!svn $Id$
!================================================== Hernan G. Arango ===
!  Copyright (c) 2002-2009 The ROMS/TOMS Group                         !
!    Licensed under a MIT/X style license                              !
!    See License_ROMS.txt                                              !
!=======================================================================
!                                                                      !
!  EcoSim Model Phytoplaknton Parameters:                              !
!                                                                      !
!                                                                      !
!  HsNO3          Half-saturation for phytoplankton NO3 uptake         !
!                   (micromole_NO3/liter).                             !
!  HsNH4          Half-saturation for phytoplankton NH4 uptake         !
!                   (micromole_NH4/liter).                             !
!  HsSiO          Half-saturation for phytoplankton SiO uptake         !
!                   (micromole_SiO/liter).                             !
!  HsPO4          Half-saturation for phytoplankton PO4 uptake         !
!                   (micromole_PO4/liter).                             !
!  HsFe           Half-saturation for phytoplankton Fe uptake          !
!                  (micromole_Fe/liter).                               !
!  GtALG_max      Maximum 24 hour growth rate (1/day).                 !
!  PhyTbase       Phytoplankton temperature base for exponential       !
!                   response to temperature (Celsius).                 !
!  PhyTfac        Phytoplankton exponential temperature factor         !
!                   (1/Celsius).                                       !
!  BET_           Nitrate uptake inhibition for NH4 (l/micromole).     !
!  maxC2nALG      Maximum phytoplankton C:N ratio                      !
!                   (micromole_C/micromole_N).                         !
!  minC2nALG      Balanced phytoplankton C:N ratio                     !
!                   (micromole_C/micromole_N).                         !
!  C2nALGminABS   Absolute minimum phytoplankton C:N ratio             !
!                   (micromole_C/micromole_N).                         !
!  maxC2SiALG     Maximum phytoplankton C:Si ratio                     !
!                   (micromole_C/micromole_Si).                        !
!  minC2SiALG     Balanced phytoplankton C:Si ratio                    !
!                   (micromole_C/micromole_Si).                        !
!  C2SiALGminABS  Absolute minimum phytoplankton C:Si ratio            !
!                  (micromole_C/micromole_Si).                         !
!  maxC2pALG      Maximum phytoplankton C:P ratio                      !
!                   (micromole_C/micromole_P).                         !
!  minC2pALG      Balanced phytoplankton C:P ratio                     !
!                   (micromole_C/micromole_P).                         !
!  C2pALGminABS   Absolute minimum phytoplankton C:P ratio             !
!                   (micromole_C/micromole_P).                         !
!  maxC2FeALG     Maximum phytoplankton C:Fe ratio                     !
!                   (micromole_C/micromole_Fe).                        !
!  minC2FeALG     Balanced phytoplankton C:Fe ratio                    !
!                   (micromole_C/micromole_Fe).                        !
!  C2FeALGminABS  Absolute minimum phytoplankton C:Fe ratio            !
!                   (micromole_C/micromole_Fe).                        !
!  qu_yld         Maximum quantum yield                                !
!                   (micromole_C/micromole_quanta).                    !
!  E0_comp        Compensation light level (micromole_quanta).         !
!  E0_inhib       Light level for onset of photoinhibition             !
!                   (micromole_quanta).                                !
!  inhib_fac      Exponential decay factor for light limited growth    !
!                   (1/micromole_quanta).                              !
!  C2Chl_max      Maximum lighted limited (nutrient replete) C:Chl     !
!                   ratio (microgram_C/microgram_Chl).                 !
!  mxC2Cl         Rate of change in the lighted limited C:Chl ratio    !
!                   (microgram_C/microgram_Chl/micromole_quanta).      !
!  b_C2Cl         Minimum lighted limited (nutrient replete) C:Chl     !
!                   ratio (microgram_C/microgram_Chl).                 !
!  mxC2Cn         Rate of change in the nutrient limited C:Chl ratio   !
!                   [(ug_C/ug_Chl)/(umole_C/umole_N)].                 !
!  b_C2Cn         Minimum nutrient limited C:Chl ratio                 !
!                   (microgram_C/microgram_Chl).                       !
!  mxPacEff       Rate of change in package effect                     !
!                   [1/(microgram_C/microgram_Chl)].                   !
!  b_PacEff       Maximum package effect                               !
!                   [1/(microgram_C/microgram_Chl)].                   !
!  mxChlB         Rate of change in the Chl_b:Chl_a ratio              !
!                   [(ug_Chl_b/ug_Chl_a)/(ug_C/ug_Chl_a)].             !
!  b_ChlB         Maximum Chl_b:Chl_a ratio                            !
!                   (microgram_Chl_b/microgram_Chl_a).                 !
!  mxChlC         Rate of change in the Chl_c:Chl_a ratio              !
!                   [(ug_Chl_c/ug_Chl_a)/(ug_C/ug_Chl_a)].             !
!  b_ChlC         Maximum Chl_c:Chl_a ratio                            !
!                   (microgram_Chl_c/microgram_Chl_a).                 !
!  mxPSC          Rate of change in the PSC:Chl_a ratio                !
!                   [(ug_PSC/ug_Chl_a)/(ug_C/ug_Chl_a)].               !
!  b_PSC          Maximum PSC:Chl_a ratio                              !
!                  (microgram_Chl_c/microgram_Chl_a).                  !
!  mxPPC          Rate of change in the PPC:Chl_a ratio                !
!                   [(ug_PPC/ug_Chl_a)/(ug_C/ug_Chl_a)].               !
!  b_PPC          Maximum PPC:Chl_a ratio                              !
!                  (microgram_Chl_c/microgram_Chl_a).                  !
!  mxLPUb         Rate of change in the LPUb:Chl_a ratio               !
!                   [(ug_LPUb/ug_Chl_a)/(ug_C/ug_Chl_a)].              !
!  b_LPUb         Maximum LPUb:Chl_a ratio                             !
!                   (microgram_HPUb/microgram_Chl_a).                  !
!  mxHPUb         Rate of change in the HPUb:Chl_a ratio               !
!                   [(ug_HPUb/ug_Chl_a)/(ug_C/ug_Chl_a)].              !
!  b_HPUb         Maximum HPUb:Chl_a ratio                             !
!                   (microgram_HPUb/microgram_Chl_a).                  !
!  FecDOC         Proportion of grazing stress which is apportioned    !
!                   to DOM (nondimensional).                           !
!  FecPEL         Proportion of grazing stress which is apportioned    !
!                   to fecal pellets (nondimesional).                  !
!  FecCYC         Proportion of grazing stress which is apportioned    !
!                   to direct remineralization (nondimensional).       !
!  ExALG          Proportion of daily production that is lost to       !
!                   excretion (nondimensional).                        !
!  WS             Phytoplankton sinking speed (meters/day).            !
!  HsGRZ          Phytoplankton grazing parameter (nondimensional).    !
!  MinRefuge      Refuge Phytoplankton population (micromole_C/liter). !
!  RefugeDep      Maximum Refuge Phytoplankton depth (meters).         !
!  Norm_Vol       Normalized Volume factor (nondimensional).           !
!  Norm_Surf      Normalized surface area factor (nondimensional).     !
!  HsDOP          Half Saturation Constant for DOP uptake              !
!                   (micromole_DOP/liter).                             !
!  C2pALKPHOS     C:P ratio where DOP uptake begins                    !
!                   (micromole_C/micromole_P).                         !
!  HsDON          Half Saturation Constant for DON uptake              !
!                   (micromole_DON/liter).                             !
!  C2nNupDON      C:N ratio where DON uptake begins                    !
!                   (micromole_C/micromole_N).                         !
!                                                                      !
! Bacteria Parameters:                                                 !
!                                                                      !
!  HsDOC_ba       Half saturation constant for bacteria DOC uptake     !
!                   (micromole_DOC/liter).                             !
!  GtBAC_max      Maximum 24 hour bacterial growth rate (1/day).       !
!  BacTbase       Phytoplankton temperature base for exponential       !
!                   response to temperature, (Celsius).                !
!  BacTfac        Phytoplankton exponential temperature factor         !
!                   (1/Celsius).                                       !
!  C2nBAC         Carbon to Nitrogen ratio of Bacteria                 !
!                   (micromole_C/micromole_N).                         !
!  C2pBAC         Carbon to Phosphorus ratio of Bacteria               !
!                   (micromole_C/micromole_P).                         !
!  C2FeBAC        Carbon to Iron ratio of Bacteria                     !
!                   (micromole_C/micromole_Fe)                         !
!  BacDOC         Proportion of bacterial grazing stress which is      !
!                   apportioned to DOM (nondimensional).               !
!  BacPEL         Proportion of bacterial grazing stress which is      !
!                   apportioned to fecal pellets (nondimensional).     !
!  BacCYC         Proportion of bacterial grazing stress which is      !
!                   apportioned to direct remineralization             !
!                   (nondimensional).                                  !
!  ExBAC_c        Bacterial recalcitrant carbon excretion as a         !
!                   proportion of uptake (nondimensional)              !
!  ExBacC2N       Bacterial recalcitrant excretion carbon to nitrogen  !
!                   ratio (micromole_C/micromole_N).                   !
!  Bac_Ceff       Bacterial gross growth carbon efficiency             !
!                   (nondimensional).                                  !
!  RtNIT          Maximum bacterial nitrification rate (1/day).        !
!  HsNIT          Half saturation constant for bacterial nitrification !
!                   (micromole NH4/liter)                              !
!                                                                      !
! Dissolved Organic Matter Parameters:                                 !
!                                                                      !
!  cDOCfrac_c     Colored fraction of DOC production from              !
!                   phytoplankton and bacterial losses                 !
!                   (nondimensional).                                  !
!  RtUVR_DIC      UV degradation of DOC into DIC at 410 nanometers     !
!                   (micromole/meter/liter/hour).                      !
!  RtUVR_DIC      UV degradation of DOC into colorless labile DOC at   !
!                   410 nanometers (micromole/meter/liter/hour).       !
!                                                                      !
! Fecal and detritus Parameters:                                       !
!                                                                      !
!  WF             Fecal sinking flux (meters/day).                     !
!  RegTbase       Fecal regeneration temperature base for exponential  !
!                   response to temperature (Celsius).                 !
!  RegTfac        Fecal regeneration exponential temperature factor    !
!                   (1/Celsius).                                       !
!  RegCR          Fecal carbon regeneration rate (1/day).              !
!  RegNR          Fecal nitrogen regeneration rate (1/day).            !
!  RegSR          Fecal silica regeneration rate (1/day).              !
!  RegPR          Fecal phosphorus regeneration rate (1/day).          !
!  RegFR          Fecal iron regeneration rate (1/day).                !
!                                                                      !
!======================================================================!
!
      USE mod_param
      USE mod_eclight
      USE mod_scalars
!
      implicit none
!
!-----------------------------------------------------------------------
!  Standard input parameters.
!-----------------------------------------------------------------------
!
!  Number of biological iterations.
!
      integer, dimension(Ngrids) :: BioIter
!
!  Control flags.
!
      logical, dimension(Ngrids) :: RtUVR_flag
      logical, dimension(Ngrids) :: NFIX_flag
      logical, dimension(Ngrids) :: Regen_flag
!
!  Phytoplankton parameters.
!
      real(r8), dimension(Nphy,Ngrids) :: HsNO3
      real(r8), dimension(Nphy,Ngrids) :: HsNH4
      real(r8), dimension(Nphy,Ngrids) :: HsSiO
      real(r8), dimension(Nphy,Ngrids) :: HsPO4
      real(r8), dimension(Nphy,Ngrids) :: HsFe
      real(r8), dimension(Nphy,Ngrids) :: GtALG_max
      real(r8), dimension(Nphy,Ngrids) :: PhyTbase
      real(r8), dimension(Nphy,Ngrids) :: PhyTfac
      real(r8), dimension(Nphy,Ngrids) :: BET_
      real(r8), dimension(Nphy,Ngrids) :: maxC2nALG
      real(r8), dimension(Nphy,Ngrids) :: minC2nALG
      real(r8), dimension(Nphy,Ngrids) :: C2nALGminABS
      real(r8), dimension(Nphy,Ngrids) :: maxC2SiALG
      real(r8), dimension(Nphy,Ngrids) :: minC2SiALG
      real(r8), dimension(Nphy,Ngrids) :: C2SiALGminABS
      real(r8), dimension(Nphy,Ngrids) :: maxC2pALG
      real(r8), dimension(Nphy,Ngrids) :: minC2pALG
      real(r8), dimension(Nphy,Ngrids) :: C2pALGminABS
      real(r8), dimension(Nphy,Ngrids) :: maxC2FeALG
      real(r8), dimension(Nphy,Ngrids) :: minC2FeALG
      real(r8), dimension(Nphy,Ngrids) :: C2FeALGminABS
      real(r8), dimension(Nphy,Ngrids) :: qu_yld
      real(r8), dimension(Nphy,Ngrids) :: E0_comp
      real(r8), dimension(Nphy,Ngrids) :: E0_inhib
      real(r8), dimension(Nphy,Ngrids) :: inhib_fac
      real(r8), dimension(Nphy,Ngrids) :: C2CHL_max
      real(r8), dimension(Nphy,Ngrids) :: mxC2Cl
      real(r8), dimension(Nphy,Ngrids) :: b_C2Cl
      real(r8), dimension(Nphy,Ngrids) :: mxC2Cn
      real(r8), dimension(Nphy,Ngrids) :: b_C2Cn
      real(r8), dimension(Nphy,Ngrids) :: mxPacEff
      real(r8), dimension(Nphy,Ngrids) :: b_PacEff
      real(r8), dimension(Nphy,Ngrids) :: mxChlB
      real(r8), dimension(Nphy,Ngrids) :: b_ChlB
      real(r8), dimension(Nphy,Ngrids) :: mxChlC
      real(r8), dimension(Nphy,Ngrids) :: b_ChlC
      real(r8), dimension(Nphy,Ngrids) :: mxPSC
      real(r8), dimension(Nphy,Ngrids) :: b_PSC
      real(r8), dimension(Nphy,Ngrids) :: mxPPC
      real(r8), dimension(Nphy,Ngrids) :: b_PPC
      real(r8), dimension(Nphy,Ngrids) :: mxLPUb
      real(r8), dimension(Nphy,Ngrids) :: b_LPUb
      real(r8), dimension(Nphy,Ngrids) :: mxHPUb
      real(r8), dimension(Nphy,Ngrids) :: b_HPUb
      real(r8), dimension(Nphy,Ngrids) :: FecDOC
      real(r8), dimension(Nphy,Nfec,Ngrids) :: FecPEL
      real(r8), dimension(Nphy,Ngrids) :: FecCYC
      real(r8), dimension(Nphy,Ngrids) :: ExALG
      real(r8), dimension(Nphy,Ngrids) :: WS
      real(r8), dimension(Nphy,Ngrids) :: HsGRZ
      real(r8), dimension(Nphy,Ngrids) :: MinRefuge
      real(r8), dimension(Nphy,Ngrids) :: RefugeDep
      real(r8), dimension(Nphy,Ngrids) :: Norm_Vol
      real(r8), dimension(Nphy,Ngrids) :: Norm_Surf
      real(r8), dimension(Nphy,Ngrids) :: HsDOP
      real(r8), dimension(Nphy,Ngrids) :: C2pALKPHOS
      real(r8), dimension(Nphy,Ngrids) :: HsDON
      real(r8), dimension(Nphy,Ngrids) :: C2nNupDON
!
!  Bacteria parameters.
!
      real(r8), dimension(Nbac,Ngrids) :: HsDOC_ba
      real(r8), dimension(Nbac,Ngrids) :: GtBAC_max
      real(r8), dimension(Nbac,Ngrids) :: BacTbase
      real(r8), dimension(Nbac,Ngrids) :: BacTfac
      real(r8), dimension(Ngrids) :: C2nBAC
      real(r8), dimension(Ngrids) :: C2pBAC
      real(r8), dimension(Ngrids) :: C2FeBAC
      real(r8), dimension(Ngrids) :: BacDOC
      real(r8), dimension(Ngrids) :: BacPEL
      real(r8), dimension(Ngrids) :: BacCYC
      real(r8), dimension(Ngrids) :: ExBAC_c
      real(r8), dimension(Ngrids) :: ExBacC2N
      real(r8), dimension(Ngrids) :: Bac_Ceff
      real(r8), dimension(Ngrids) :: RtNIT
      real(r8), dimension(Ngrids) :: HsNIT
!
!  DOM parameters.
!
      real(r8), dimension(Ndom,Ngrids) :: cDOCfrac_c
      real(r8), dimension(Ngrids) :: RtUVR_DIC
      real(r8), dimension(Ngrids) :: RtUVR_DOC
!
!  Fecal parameters.
!
      real(r8), dimension(Nfec,Ngrids) :: WF
      real(r8), dimension(Nfec,Ngrids) :: RegTbase
      real(r8), dimension(Nfec,Ngrids) :: RegTfac
      real(r8), dimension(Nfec,Ngrids) :: RegCR
      real(r8), dimension(Nfec,Ngrids) :: RegNR
      real(r8), dimension(Nfec,Ngrids) :: RegSR
      real(r8), dimension(Nfec,Ngrids) :: RegPR
      real(r8), dimension(Nfec,Ngrids) :: RegFR
!
!-----------------------------------------------------------------------
!  Internal parameters.
!-----------------------------------------------------------------------
!
!  Spectral band width used in light calculations.

      real(r8), parameter :: DLAM  = 5.0_r8
!
!  Flags used for testing purposes.
!
      real(r8), parameter :: SMALL  = 1.0e-6_r8
      real(r8), parameter :: VSMALL = 1.0e-14_r8
      real(r8), parameter :: LARGE  = 1.0e+10_r8
      real(r8), parameter :: VLARGE = 1.0e+50_r8
!
!  Array indexes for frequently used constituents.
!
      integer, parameter :: ilab=1    ! labile index for DOC.
      integer, parameter :: irct=2    ! relict index for DOC.
      integer, parameter :: ichl=1    ! pigment index for chlorophyll-a
      integer, parameter :: isfc=1    ! slow fecal pellet index
      integer, parameter :: iffc=2    ! fast fecal pellet index
!
!  Phytoplankton calculated paramters.
!
      real(r8), dimension(Nphy,Ngrids) :: ImaxC2nALG   ! inverse C2nALG
      real(r8), dimension(Nphy,Ngrids) :: ImaxC2SiALG  ! inverse C2SiALG
      real(r8), dimension(Nphy,Ngrids) :: ImaxC2pALG   ! inverse C2pALG
      real(r8), dimension(Nphy,Ngrids) :: ImaxC2FeALG  ! inverse C2FeALG
!
!  Bacteria calculated parameters.
!
      real(r8), dimension(Ngrids) :: N2cBAC
      real(r8), dimension(Ngrids) :: P2cBAC
      real(r8), dimension(Ngrids) :: Fe2cBAC
      real(r8), dimension(Nbac,Ngrids) :: HsNH4_ba
      real(r8), dimension(Nbac,Ngrids) :: HsPO4_ba
      real(r8), dimension(Nbac,Ngrids) :: HsFe_ba
      real(r8), dimension(Ngrids) :: R_ExBAC_c
      real(r8), dimension(Ngrids) :: ExBAC_n
      real(r8), dimension(Ngrids) :: Frac_ExBAC_n
      real(r8), dimension(Ngrids) :: I_Bac_Ceff
!
!  Absorption parameters.
!
      real(r8), dimension(NBands) :: wavedp   ! a and b factor
      real(r8), dimension(Ndom) :: aDOC410    ! CDM absorption at 410
      real(r8), dimension(Ndom) :: aDOC300    ! CDM absorption at 300

      CONTAINS

      SUBROUTINE initialize_biology
!
!=======================================================================
!                                                                      !
!  This routine initializes several parameters in module "mod_biology" !
!  for all nested grids.                                               !
!                                                                      !
!=======================================================================
!
!  Local variable declarations
!
      integer :: ibac, iband, ifec, iphy, ng
!
!-----------------------------------------------------------------------
!  Derived parameters.
!-----------------------------------------------------------------------
!
!  Convert rates from day-1 to second-1.
!
      DO ng=1,Ngrids
        DO iphy=1,Nphy
          GtALG_max(iphy,ng)=GtALG_max(iphy,ng)*sec2day
          ExALG(iphy,ng)=ExALG(iphy,ng)*sec2day
          HsGRZ(iphy,ng)=HsGRZ(iphy,ng)*sec2day
          WS(iphy,ng)=WS(iphy,ng)*sec2day
        END DO
        DO ibac=1,Nbac
          GtBAC_max(ibac,ng)=GtBAC_max(ibac,ng)*sec2day
        END DO
        DO ifec=1,Nfec
          WF(ifec,ng)=WF(ifec,ng)*sec2day
        END DO
        RtNIT(ng)=RtNIT(ng)*sec2day
      END DO
!
!  Calculated reciprocal phytoplankton parameters.
!
      DO ng=1,Ngrids
        DO iphy=1,Nphy
          IF (maxC2nALG(iphy,ng).gt.SMALL) THEN
            ImaxC2nALG(iphy,ng)=1.0_r8/maxC2nALG(iphy,ng)
          ELSE
            ImaxC2nALG(iphy,ng)=0.0_r8
          END IF
          IF (maxC2SiALG(iphy,ng).gt.SMALL) THEN
            ImaxC2SiALG(iphy,ng)=1.0_r8/maxC2SiALG(iphy,ng)
          ELSE
            ImaxC2SiALG(iphy,ng)=0.0_r8
          END IF
          IF (maxC2pALG(iphy,ng).gt.SMALL) THEN
            ImaxC2pALG(iphy,ng)=1.0_r8/maxC2pALG(iphy,ng)
          ELSE
            ImaxC2pALG(iphy,ng)=0.0_r8
          END IF
          IF (maxC2FeALG(iphy,ng).gt.SMALL) THEN
            ImaxC2FeALG(iphy,ng)=1.0_r8/maxC2FeALG(iphy,ng)
          ELSE
            ImaxC2FeALG(iphy,ng)=0.0_r8
          END IF
        END DO
      END DO
!
!  Calculated bacterial parameters.
!
      DO ng=1,Ngrids
        DO ibac=1,Nbac
          HsNH4_ba(ibac,ng)=HsDOC_ba(ibac,ng)/C2nBAC(ng)
          HsPO4_ba(ibac,ng)=HsDOC_ba(ibac,ng)/C2pBAC(ng)
          HsFe_ba (ibac,ng)=HsDOC_ba(ibac,ng)/C2FeBAC(ng)
        END DO
      END DO
!
!  Inverse parameters for computational efficiency.
!
      DO ng=1,Ngrids
        N2cBAC(ng)=1.0_r8/C2nBAC(ng)
        P2cBAC(ng)=1.0_r8/C2pBAC(ng)
        Fe2cBAC(ng)=1.0_r8/C2FeBAC(ng)
        I_Bac_Ceff(ng)=1.0_r8/Bac_Ceff(ng)
      END DO
!
!  Reciprocal of non baterial recalcitran carbon excretion.
!
      DO ng=1,Ngrids
        R_ExBAC_c(ng)=1.0_r8/(1.0_r8-ExBAC_c(ng))
      END DO
!
!  Bacterial recalcitrant nitrogen excretion as a function of uptake.
!
      DO ng=1,Ngrids
        ExBAC_n(ng)=ExBAC_c(ng)*C2nBAC(ng)/ExBacC2N(ng)
        Frac_ExBAC_n(ng)=1.0_r8-ExBAC_n(ng)
      END DO
!
!  Scale UV degradation parameters.
!
      DO ng=1,Ngrids
        RtUVR_DIC(ng)=RtUVR_DIC(ng)/3600.0_r8
        RtUVR_DOC(ng)=RtUVR_DOC(ng)/3600.0_r8
      END DO
!
!  If applicable, zero-out fecal regeneration parameters.
!
      DO ng=1,Ngrids
        IF (Regen_flag(ng)) THEN
          DO ifec=1,Nfec
            RegCR(ifec,ng)=RegCR(ifec,ng)*sec2day
            RegNR(ifec,ng)=RegNR(ifec,ng)*sec2day
            RegPR(ifec,ng)=RegPR(ifec,ng)*sec2day
            RegFR(ifec,ng)=RegFR(ifec,ng)*sec2day
            RegSR(ifec,ng)=RegSR(ifec,ng)*sec2day
          END DO
        ELSE
          DO ifec=1,Nfec
            RegCR(ifec,ng)=0.0_r8
            RegNR(ifec,ng)=0.0_r8
            RegPR(ifec,ng)=0.0_r8
            RegFR(ifec,ng)=0.0_r8
            RegSR(ifec,ng)=0.0_r8
          END DO
        END IF
      END DO
!
!  Spectral dependency for scattering and backscattering.
!
      DO iband=1,NBands
        wavedp(iband)=(550.0_r8/(397.0_r8+REAL(iband,r8)*DLAM))
      END DO
!
!  Calculated IOP parameter values.
!
      aDOC410(ilab)=aDOC(ilab,1)*EXP(0.014_r8*(ec_wave_ab(1)-410.0_r8))
      aDOC410(irct)=aDOC(irct,1)*EXP(0.025_r8*(ec_wave_ab(1)-410.0_r8))
      aDOC300(ilab)=EXP(0.0145_r8*(410.0_r8-300.0_r8))
      aDOC300(irct)=EXP(0.0145_r8*(410.0_r8-300.0_r8))

      RETURN
      END SUBROUTINE initialize_biology