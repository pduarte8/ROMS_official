#ifdef EW_PERIODIC
# define I_RANGE Istr-1,Iend+1
#else
# define I_RANGE MAX(Istr-1,1),MIN(Iend+1,Lm(ng))
#endif
#ifdef NS_PERIODIC
# define J_RANGE Jstr-1,Jend+1
#else
# define J_RANGE MAX(Jstr-1,1),MIN(Jend+1,Mm(ng))
#endif

      SUBROUTINE tl_t3dmix4 (ng, tile)
!
!svn $Id$
!************************************************** Hernan G. Arango ***
!  Copyright (c) 2002-2008 The ROMS/TOMS Group       Andrew M. Moore   !
!    Licensed under a MIT/X style license                              !
!    See License_ROMS.txt                                              !
!***********************************************************************
!                                                                      !
!  This subroutine computes tangent linear horizontal biharmonic       !
!  mixing of tracers along geopotential surfaces.                      !
!                                                                      !
!  BASIC STATE variables needed: diff4, Hz, t, z_r                     !
!                                                                      !
!***********************************************************************
!
      USE mod_param
#ifdef DIAGNOSTICS_TS
!!    USE mod_diags
#endif
      USE mod_grid
      USE mod_mixing
      USE mod_ocean
      USE mod_stepping
!
!  Imported variable declarations.
!
      integer, intent(in) :: ng, tile
!
!  Local variable declarations.
!
#include "tile.h"
!
#ifdef PROFILE
      CALL wclock_on (ng, iTLM, 28)
#endif
      CALL tl_t3dmix4_tile (ng, Istr, Iend, Jstr, Jend,                 &
     &                      LBi, UBi, LBj, UBj,                         &
     &                      nrhs(ng), nnew(ng),                         &
#ifdef MASKING
     &                      GRID(ng) % umask,                           &
     &                      GRID(ng) % vmask,                           &
#endif
     &                      GRID(ng) % om_v,                            &
     &                      GRID(ng) % on_u,                            &
     &                      GRID(ng) % pm,                              &
     &                      GRID(ng) % pn,                              &
     &                      GRID(ng) % Hz,                              &
     &                      GRID(ng) % tl_Hz,                           &
     &                      GRID(ng) % z_r,                             &
     &                      GRID(ng) % tl_z_r,                          &
     &                      MIXING(ng) % diff4,                         &
#ifdef DIAGNOSTICS_TS
!!   &                      DIAGS(ng) % DiaTwrk,                        &
#endif
     &                      OCEAN(ng) % t,                              &
     &                      OCEAN(ng) % tl_t)
#ifdef PROFILE
      CALL wclock_off (ng, iTLM, 28)
#endif
      RETURN
      END SUBROUTINE tl_t3dmix4
!
!***********************************************************************
      SUBROUTINE tl_t3dmix4_tile (ng, Istr, Iend, Jstr, Jend,           &
     &                            LBi, UBi, LBj, UBj,                   &
     &                            nrhs, nnew,                           &
#ifdef MASKING
     &                            umask, vmask,                         &
#endif
     &                            om_v, on_u, pm, pn,                   &
     &                            Hz, tl_Hz,                            &
     &                            z_r, tl_z_r,                          &
     &                            diff4,                                &
#ifdef DIAGNOSTICS_TS
!!   &                            DiaTwrk,                              &
#endif
     &                            t, tl_t)
!***********************************************************************
!
      USE mod_param
      USE mod_scalars
!
!  Imported variable declarations.
!
      integer, intent(in) :: ng, Iend, Istr, Jend, Jstr
      integer, intent(in) :: LBi, UBi, LBj, UBj
      integer, intent(in) :: nrhs, nnew

#ifdef ASSUMED_SHAPE
# ifdef MASKING
      real(r8), intent(in) :: umask(LBi:,LBj:)
      real(r8), intent(in) :: vmask(LBi:,LBj:)
# endif
      real(r8), intent(in) :: diff4(LBi:,LBj:,:)
      real(r8), intent(in) :: om_v(LBi:,LBj:)
      real(r8), intent(in) :: on_u(LBi:,LBj:)
      real(r8), intent(in) :: pm(LBi:,LBj:)
      real(r8), intent(in) :: pn(LBi:,LBj:)
      real(r8), intent(in) :: Hz(LBi:,LBj:,:)
      real(r8), intent(in) :: z_r(LBi:,LBj:,:)
      real(r8), intent(in) :: t(LBi:,LBj:,:,:,:)

      real(r8), intent(in) :: tl_Hz(LBi:,LBj:,:)
      real(r8), intent(in) :: tl_z_r(LBi:,LBj:,:)
# ifdef DIAGNOSTICS_TS
      real(r8), intent(inout) :: DiaTwrk(LBi:,LBj:,:,:,:)
# endif
      real(r8), intent(inout) :: tl_t(LBi:,LBj:,:,:,:)
#else
# ifdef MASKING
      real(r8), intent(in) :: umask(LBi:UBi,LBj:UBj)
      real(r8), intent(in) :: vmask(LBi:UBi,LBj:UBj)
# endif
      real(r8), intent(in) :: diff4(LBi:UBi,LBj:UBj,NT(ng))
      real(r8), intent(in) :: om_v(LBi:UBi,LBj:UBj)
      real(r8), intent(in) :: on_u(LBi:UBi,LBj:UBj)
      real(r8), intent(in) :: pm(LBi:UBi,LBj:UBj)
      real(r8), intent(in) :: pn(LBi:UBi,LBj:UBj)
      real(r8), intent(in) :: Hz(LBi:UBi,LBj:UBj,N(ng))
      real(r8), intent(in) :: z_r(LBi:UBi,LBj:UBj,N(ng))
      real(r8), intent(in) :: t(LBi:UBi,LBj:UBj,N(ng),3,NT(ng))

      real(r8), intent(in) :: tl_Hz(LBi:UBi,LBj:UBj,N(ng))
      real(r8), intent(in) :: tl_z_r(LBi:UBi,LBj:UBj,N(ng))
# ifdef DIAGNOSTICS_TS
!!    real(r8), intent(inout) :: DiaTwrk(LBi:UBi,LBj:UBj,N(ng),NT(ng),  &
!!   &                                   NDT)
# endif
      real(r8), intent(inout) :: tl_t(LBi:UBi,LBj:UBj,N(ng),3,NT(ng))
#endif
!
!  Local variable declarations.
!
      integer :: IstrR, IendR, JstrR, JendR, IstrU, JstrV
      integer :: i, itrc, j, k, k1, k2

      real(r8) :: cff, cff1, cff2, cff3, cff4
      real(r8) :: tl_cff, tl_cff1, tl_cff2, tl_cff3, tl_cff4

      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,N(ng)) :: LapT

      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,N(ng)) :: tl_LapT

      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY) :: FE
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY) :: FX

      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY) :: tl_FE
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY) :: tl_FX

      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: FS
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: dTde
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: dTdx
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: dTdz
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: dZde
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: dZdx

      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: tl_FS
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: tl_dTde
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: tl_dTdx
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: tl_dTdz
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: tl_dZde
      real(r8), dimension(PRIVATE_2D_SCRATCH_ARRAY,2) :: tl_dZdx

#include "set_bounds.h"
!
!-----------------------------------------------------------------------
!  Compute tangent linear horizontal biharmonic diffusion along
!  geopotential surfaces.  The biharmonic operator is computed by
!  applying the harmonic operator twice.
!-----------------------------------------------------------------------
!
!  Compute horizontal and vertical gradients associated with the
!  first rotated harmonic operator.  Notice the recursive blocking
!  sequence. The vertical placement of the gradients is:
!
!        dTdx,dTde(:,:,k1) k     rho-points
!        dTdx,dTde(:,:,k2) k+1   rho-points
!          FS,dTdz(:,:,k1) k-1/2   W-points
!          FS,dTdz(:,:,k2) k+1/2   W-points
!
      T_LOOP : DO itrc=1,NT(ng)
        k2=1
        K_LOOP1 : DO k=0,N(ng)
          k1=k2
          k2=3-k1
          IF (k.lt.N(ng)) THEN
            DO j=J_RANGE
              DO i=I_RANGE+1
                cff=0.5_r8*(pm(i,j)+pm(i-1,j))
#ifdef MASKING
                cff=cff*umask(i,j)
#endif
                dZdx(i,j,k2)=cff*(z_r(i  ,j,k+1)-                       &
     &                            z_r(i-1,j,k+1))
                tl_dZdx(i,j,k2)=cff*(tl_z_r(i  ,j,k+1)-                 &
     &                               tl_z_r(i-1,j,k+1))
                dTdx(i,j,k2)=cff*(t(i  ,j,k+1,nrhs,itrc)-               &
     &                            t(i-1,j,k+1,nrhs,itrc))
                tl_dTdx(i,j,k2)=cff*(tl_t(i  ,j,k+1,nrhs,itrc)-         &
     &                               tl_t(i-1,j,k+1,nrhs,itrc))
              END DO
            END DO
            DO j=J_RANGE+1
              DO i=I_RANGE
                cff=0.5_r8*(pn(i,j)+pn(i,j-1))
#ifdef MASKING
                cff=cff*vmask(i,j)
#endif
                dZde(i,j,k2)=cff*(z_r(i,j  ,k+1)-                       &
     &                            z_r(i,j-1,k+1))
                tl_dZde(i,j,k2)=cff*(tl_z_r(i,j  ,k+1)-                 &
     &                               tl_z_r(i,j-1,k+1))
                dTde(i,j,k2)=cff*(t(i,j  ,k+1,nrhs,itrc)-               &
     &                            t(i,j-1,k+1,nrhs,itrc))
                tl_dTde(i,j,k2)=cff*(tl_t(i,j  ,k+1,nrhs,itrc)-         &
     &                               tl_t(i,j-1,k+1,nrhs,itrc))
              END DO
            END DO
          END IF
          IF ((k.eq.0).or.(k.eq.N(ng))) THEN
            DO j=-1+J_RANGE+1
              DO i=-1+I_RANGE+1
                dTdz(i,j,k2)=0.0_r8
                tl_dTdz(i,j,k2)=0.0_r8
                FS(i,j,k2)=0.0_r8
                tl_FS(i,j,k2)=0.0_r8
              END DO
            END DO
          ELSE
            DO j=-1+J_RANGE+1
              DO i=-1+I_RANGE+1
                cff=1.0_r8/(z_r(i,j,k+1)-                               &
     &                      z_r(i,j,k  ))
                tl_cff=-cff*cff*(tl_z_r(i,j,k+1)-                       &
     &                           tl_z_r(i,j,k  ))
                dTdz(i,j,k2)=cff*(t(i,j,k+1,nrhs,itrc)-                 &
     &                            t(i,j,k  ,nrhs,itrc))
                tl_dTdz(i,j,k2)=tl_cff*(t(i,j,k+1,nrhs,itrc)-           &
     &                                  t(i,j,k  ,nrhs,itrc))+          &
     &                          cff*(tl_t(i,j,k+1,nrhs,itrc)-           &
     &                               tl_t(i,j,k  ,nrhs,itrc))
              END DO
            END DO
          END IF
          IF (k.gt.0) THEN
            DO j=J_RANGE
              DO i=I_RANGE+1
                cff=0.25_r8*(diff4(i,j,itrc)+diff4(i-1,j,itrc))*        &
     &              on_u(i,j)
                FX(i,j)=cff*                                            &
     &                  (Hz(i,j,k)+Hz(i-1,j,k))*                        &
     &                  (dTdx(i,j,k1)-                                  &
     &                   0.5_r8*(MIN(dZdx(i,j,k1),0.0_r8)*              &
     &                              (dTdz(i-1,j,k1)+                    &
     &                               dTdz(i  ,j,k2))+                   &
     &                           MAX(dZdx(i,j,k1),0.0_r8)*              &
     &                              (dTdz(i-1,j,k2)+                    &
     &                               dTdz(i  ,j,k1))))
                tl_FX(i,j)=cff*                                         &
     &                     ((tl_Hz(i,j,k)+tl_Hz(i-1,j,k))*              &
     &                      (dTdx(i,j,k1)-                              &
     &                       0.5_r8*(MIN(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i-1,j,k1)+                &
     &                                   dTdz(i  ,j,k2))+               &
     &                               MAX(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i-1,j,k2)+                &
     &                                   dTdz(i  ,j,k1))))+             &
     &                      (Hz(i,j,k)+Hz(i-1,j,k))*                    &
     &                      (tl_dTdx(i,j,k1)-                           &
     &                       0.5_r8*(MIN(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i-1,j,k1)+             &
     &                                   tl_dTdz(i  ,j,k2))+            &
     &                               MAX(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i-1,j,k2)+             &
     &                                   tl_dTdz(i  ,j,k1)))-           &
     &                       0.5_r8*((0.5_r8+                           &
     &                                SIGN(0.5_r8,-dZdx(i,j,k1)))*      &
     &                               tl_dZdx(i,j,k1)*                   &
     &                               (dTdz(i-1,j,k1)+dTdz(i,j,k2))+     &
     &                               (0.5_r8+                           &
     &                                SIGN(0.5_r8, dZdx(i,j,k1)))*      &
     &                               tl_dZdx(i,j,k1)*                   &
     &                               (dTdz(i-1,j,k2)+dTdz(i,j,k1)))))
              END DO
            END DO
            DO j=J_RANGE+1
              DO i=I_RANGE
                cff=0.25_r8*(diff4(i,j,itrc)+diff4(i,j-1,itrc))*        &
     &              om_v(i,j)
                FE(i,j)=cff*                                            &
     &                  (Hz(i,j,k)+Hz(i,j-1,k))*                        &
     &                  (dTde(i,j,k1)-                                  &
     &                   0.5_r8*(MIN(dZde(i,j,k1),0.0_r8)*              &
     &                              (dTdz(i,j-1,k1)+                    &
     &                               dTdz(i,j  ,k2))+                   &
     &                           MAX(dZde(i,j,k1),0.0_r8)*              &
     &                              (dTdz(i,j-1,k2)+                    &
     &                               dTdz(i,j  ,k1))))
                tl_FE(i,j)=cff*                                         &
     &                     ((tl_Hz(i,j,k)+tl_Hz(i,j-1,k))*              &
     &                      (dTde(i,j,k1)-                              &
     &                       0.5_r8*(MIN(dZde(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i,j-1,k1)+                &
     &                                   dTdz(i,j  ,k2))+               &
     &                               MAX(dZde(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i,j-1,k2)+                &
     &                                   dTdz(i,j  ,k1))))+             &
     &                      (Hz(i,j,k)+Hz(i,j-1,k))*                    &
     &                      (tl_dTde(i,j,k1)-                           &
     &                       0.5_r8*(MIN(dZde(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i,j-1,k1)+             &
     &                                   tl_dTdz(i,j  ,k2))+            &
     &                               MAX(dZde(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i,j-1,k2)+             &
     &                                   tl_dTdz(i,j  ,k1)))-           &
     &                       0.5_r8*((0.5_r8+                           &
     &                                SIGN(0.5_r8,-dZde(i,j,k1)))*      &
     &                               tl_dZde(i,j,k1)*                   &
     &                               (dTdz(i,j-1,k1)+dTdz(i,j,k2))+     &
     &                               (0.5_r8+                           &
     &                                SIGN(0.5_r8, dZde(i,j,k1)))*      &
     &                               tl_dZde(i,j,k1)*                   &
     &                               (dTdz(i,j-1,k2)+dTdz(i,j,k1)))))
              END DO
            END DO
            IF (k.lt.N(ng)) THEN
              DO j=J_RANGE
                DO i=I_RANGE
                  cff=0.5_r8*diff4(i,j,itrc)
                  cff1=MIN(dZdx(i  ,j,k1),0.0_r8)
                  cff2=MIN(dZdx(i+1,j,k2),0.0_r8)
                  cff3=MAX(dZdx(i  ,j,k2),0.0_r8)
                  cff4=MAX(dZdx(i+1,j,k1),0.0_r8)
                  tl_cff1=(0.5_r8+SIGN(0.5_r8,-dZdx(i  ,j,k1)))*        &
     &                    tl_dZdx(i  ,j,k1)
                  tl_cff2=(0.5_r8+SIGN(0.5_r8,-dZdx(i+1,j,k2)))*        &
     &                    tl_dZdx(i+1,j,k2)
                  tl_cff3=(0.5_r8+SIGN(0.5_r8, dZdx(i  ,j,k2)))*        &
     &                    tl_dZdx(i  ,j,k2)
                  tl_cff4=(0.5_r8+SIGN(0.5_r8, dZdx(i+1,j,k1)))*        &
     &                    tl_dZdx(i+1,j,k1)
                  FS(i,j,k2)=cff*                                       &
     &                       (cff1*(cff1*dTdz(i,j,k2)-                  &
     &                              dTdx(i  ,j,k1))+                    &
     &                        cff2*(cff2*dTdz(i,j,k2)-                  &
     &                              dTdx(i+1,j,k2))+                    &
     &                        cff3*(cff3*dTdz(i,j,k2)-                  &
     &                              dTdx(i  ,j,k2))+                    &
     &                        cff4*(cff4*dTdz(i,j,k2)-                  &
     &                              dTdx(i+1,j,k1)))
                  tl_FS(i,j,k2)=cff*                                    &
     &                          (tl_cff1*(cff1*dTdz(i,j,k2)-            &
     &                                    dTdx(i  ,j,k1))+              &
     &                           tl_cff2*(cff2*dTdz(i,j,k2)-            &
     &                                    dTdx(i+1,j,k2))+              &
     &                           tl_cff3*(cff3*dTdz(i,j,k2)-            &
     &                                    dTdx(i  ,j,k2))+              &
     &                           tl_cff4*(cff4*dTdz(i,j,k2)-            &
     &                                    dTdx(i+1,j,k1))+              &
     &                           cff1*(tl_cff1*dTdz(i,j,k2)+            &
     &                                 cff1*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i  ,j,k1))+              &
     &                           cff2*(tl_cff2*dTdz(i,j,k2)+            &
     &                                 cff2*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i+1,j,k2))+              &
     &                           cff3*(tl_cff3*dTdz(i,j,k2)+            &
     &                                 cff3*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i  ,j,k2))+              &
     &                           cff4*(tl_cff4*dTdz(i,j,k2)+            &
     &                                 cff4*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i+1,j,k1)))
                  cff1=MIN(dZde(i,j  ,k1),0.0_r8)
                  cff2=MIN(dZde(i,j+1,k2),0.0_r8)
                  cff3=MAX(dZde(i,j  ,k2),0.0_r8)
                  cff4=MAX(dZde(i,j+1,k1),0.0_r8)
                  tl_cff1=(0.5_r8+SIGN(0.5_r8,-dZde(i,j  ,k1)))*        &
     &                    tl_dZde(i,j  ,k1)
                  tl_cff2=(0.5_r8+SIGN(0.5_r8,-dZde(i,j+1,k2)))*        &
     &                    tl_dZde(i,j+1,k2)
                  tl_cff3=(0.5_r8+SIGN(0.5_r8, dZde(i,j  ,k2)))*        &
     &                    tl_dZde(i,j  ,k2)
                  tl_cff4=(0.5_r8+SIGN(0.5_r8, dZde(i,j+1,k1)))*        &
     &                    tl_dZde(i,j+1,k1)
                  FS(i,j,k2)=FS(i,j,k2)+                                &
     &                       cff*                                       &
     &                       (cff1*(cff1*dTdz(i,j,k2)-                  &
     &                              dTde(i,j  ,k1))+                    &
     &                        cff2*(cff2*dTdz(i,j,k2)-                  &
     &                              dTde(i,j+1,k2))+                    &
     &                        cff3*(cff3*dTdz(i,j,k2)-                  &
     &                              dTde(i,j  ,k2))+                    &
     &                        cff4*(cff4*dTdz(i,j,k2)-                  &
     &                              dTde(i,j+1,k1)))
                  tl_FS(i,j,k2)=tl_FS(i,j,k2)+                          &
     &                          cff*                                    &
     &                          (tl_cff1*(cff1*dTdz(i,j,k2)-            &
     &                                    dTde(i,j  ,k1))+              &
     &                           tl_cff2*(cff2*dTdz(i,j,k2)-            &
     &                                    dTde(i,j+1,k2))+              &
     &                           tl_cff3*(cff3*dTdz(i,j,k2)-            &
     &                                    dTde(i,j  ,k2))+              &
     &                           tl_cff4*(cff4*dTdz(i,j,k2)-            &
     &                                    dTde(i,j+1,k1))+              &
     &                           cff1*(tl_cff1*dTdz(i,j,k2)+            &
     &                                 cff1*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j  ,k1))+              &
     &                           cff2*(tl_cff2*dTdz(i,j,k2)+            &
     &                                 cff2*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j+1,k2))+              &
     &                           cff3*(tl_cff3*dTdz(i,j,k2)+            &
     &                                 cff3*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j  ,k2))+              &
     &                           cff4*(tl_cff4*dTdz(i,j,k2)+            &
     &                                 cff4*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j+1,k1)))
                END DO
              END DO
            END IF
!
!  Compute first harmonic operator, without mixing coefficient.
!  Multiply by the metrics of the second harmonic operator.  Save
!  into work array "LapT".
!
            DO j=J_RANGE
              DO i=I_RANGE
                cff=pm(i,j)*pn(i,j)
                cff1=1.0_r8/Hz(i,j,k)
                tl_cff1=-cff1*cff1*tl_Hz(i,j,k)
                LapT(i,j,k)=cff1*(cff*                                  &
     &                            (FX(i+1,j)-FX(i,j)+                   &
     &                             FE(i,j+1)-FE(i,j))+                  &
     &                            (FS(i,j,k2)-FS(i,j,k1)))
                tl_LapT(i,j,k)=tl_cff1*(cff*                            &
     &                                  (FX(i+1,j)-FX(i,j)+             &
     &                                   FE(i,j+1)-FE(i,j))+            &
     &                                  (FS(i,j,k2)-FS(i,j,k1)))+       &
     &                         cff1*(cff*                               &
     &                               (tl_FX(i+1,j)-tl_FX(i,j)+          &
     &                                tl_FE(i,j+1)-tl_FE(i,j))+         &
     &                               (tl_FS(i,j,k2)-tl_FS(i,j,k1)))
              END DO
            END DO
          END IF
        END DO K_LOOP1
!
!  Apply boundary conditions (except periodic; closed or gradient)
!  to the first harmonic operator.
!
#ifndef EW_PERIODIC
        IF (WESTERN_EDGE) THEN
          DO k=1,N(ng)
            DO j=J_RANGE
# ifdef WESTERN_WALL
              LapT(Istr-1,j,k)=0.0_r8
              tl_LapT(Istr-1,j,k)=0.0_r8
# else
              LapT(Istr-1,j,k)=LapT(Istr,j,k)
              tl_LapT(Istr-1,j,k)=tl_LapT(Istr,j,k)
# endif
            END DO
          END DO
        END IF
        IF (EASTERN_EDGE) THEN
          DO k=1,N(ng)
            DO j=J_RANGE
# ifdef EASTERN_WALL
              LapT(Iend+1,j,k)=0.0_r8
              tl_LapT(Iend+1,j,k)=0.0_r8
# else
              LapT(Iend+1,j,k)=LapT(Iend,j,k)
              tl_LapT(Iend+1,j,k)=tl_LapT(Iend,j,k)
# endif
            END DO
          END DO
        END IF
#endif
#ifndef NS_PERIODIC
        IF (SOUTHERN_EDGE) THEN
          DO k=1,N(ng)
            DO i=I_RANGE
# ifdef SOUTHERN_WALL
              LapT(i,Jstr-1,k)=0.0_r8
              tl_LapT(i,Jstr-1,k)=0.0_r8
# else
              LapT(i,Jstr-1,k)=LapT(i,Jstr,k)
              tl_LapT(i,Jstr-1,k)=tl_LapT(i,Jstr,k)
# endif
            END DO
          END DO
        END IF
        IF (NORTHERN_EDGE) THEN
          DO k=1,N(ng)
            DO i=I_RANGE
# ifdef NORTHERN_WALL
              LapT(i,Jend+1,k)=0.0_r8
              tl_LapT(i,Jend+1,k)=0.0_r8
# else
              LapT(i,Jend+1,k)=LapT(i,Jend,k)
              tl_LapT(i,Jend+1,k)=tl_LapT(i,Jend,k)
# endif
            END DO
          END DO
        END IF
#endif
#if !defined EW_PERIODIC && !defined NS_PERIODIC
        IF ((SOUTHERN_EDGE).and.(WESTERN_EDGE)) THEN
          DO k=1,N(ng)
            LapT(Istr-1,Jstr-1,k)=0.5_r8*(LapT(Istr  ,Jstr-1,k)+        &
     &                                    LapT(Istr-1,Jstr  ,k))
            tl_LapT(Istr-1,Jstr-1,k)=0.5_r8*(tl_LapT(Istr  ,Jstr-1,k)+  &
                                             tl_LapT(Istr-1,Jstr  ,k))
          END DO
        END IF
        IF ((SOUTHERN_EDGE).and.(EASTERN_EDGE)) THEN
          DO k=1,N(ng)
            LapT(Iend+1,Jstr-1,k)=0.5_r8*(LapT(Iend  ,Jstr-1,k)+        &
     &                                    LapT(Iend+1,Jstr  ,k))
            tl_LapT(Iend+1,Jstr-1,k)=0.5_r8*(tl_LapT(Iend  ,Jstr-1,k)+  &
     &                                       tl_LapT(Iend+1,Jstr  ,k))
          END DO
        END IF
        IF ((NORTHERN_EDGE).and.(WESTERN_EDGE)) THEN
          DO k=1,N(ng)
            LapT(Istr-1,Jend+1,k)=0.5_r8*(LapT(Istr  ,Jend+1,k)+        &
     &                                    LapT(Istr-1,Jend  ,k))
            tl_LapT(Istr-1,Jend+1,k)=0.5_r8*(tl_LapT(Istr  ,Jend+1,k)+  &
     &                                       tl_LapT(Istr-1,Jend  ,k))
          END DO
        END IF
        IF ((NORTHERN_EDGE).and.(EASTERN_EDGE)) THEN
          DO k=1,N(ng)
            LapT(Iend+1,Jend+1,k)=0.5_r8*(LapT(Iend  ,Jend+1,k)+        &
     &                                    LapT(Iend+1,Jend  ,k))
            tl_LapT(Iend+1,Jend+1,k)=0.5_r8*(tl_LapT(Iend  ,Jend+1,k)+  &
     &                                       tl_LapT(Iend+1,Jend  ,k))
          END DO
        END IF
#endif
!
!  Compute tangent linear horizontal and vertical gradients associated
!  with the second rotated harmonic operator.
!
        k2=1
        K_LOOP2: DO k=0,N(ng)
          k1=k2
          k2=3-k1
          IF (k.lt.N(ng)) THEN
            DO j=Jstr,Jend
              DO i=Istr,Iend+1
                cff=0.5_r8*(pm(i,j)+pm(i-1,j))
#ifdef MASKING
                cff=cff*umask(i,j)
#endif
                dZdx(i,j,k2)=cff*(z_r(i  ,j,k+1)-                       &
     &                            z_r(i-1,j,k+1))
                tl_dZdx(i,j,k2)=cff*(tl_z_r(i  ,j,k+1)-                 &
     &                               tl_z_r(i-1,j,k+1))
                dTdx(i,j,k2)=cff*(LapT(i  ,j,k+1)-                      &
     &                            LapT(i-1,j,k+1))
                tl_dTdx(i,j,k2)=cff*(tl_LapT(i  ,j,k+1)-                &
     &                               tl_LapT(i-1,j,k+1))
              END DO
            END DO
            DO j=Jstr,Jend+1
              DO i=Istr,Iend
                cff=0.5_r8*(pn(i,j)+pn(i,j-1))
#ifdef MASKING
                cff=cff*vmask(i,j)
#endif
                dZde(i,j,k2)=cff*(z_r(i,j  ,k+1)-                       &
     &                            z_r(i,j-1,k+1))
                tl_dZde(i,j,k2)=cff*(tl_z_r(i,j  ,k+1)-                 &
     &                               tl_z_r(i,j-1,k+1))
                dTde(i,j,k2)=cff*(LapT(i,j  ,k+1)-                      &
     &                            LapT(i,j-1,k+1))
                tl_dTde(i,j,k2)=cff*(tl_LapT(i,j  ,k+1)-                &
     &                               tl_LapT(i,j-1,k+1))
              END DO
            END DO
          END IF
          IF ((k.eq.0).or.(k.eq.N(ng))) THEN
            DO j=Jstr-1,Jend+1
              DO i=Istr-1,Iend+1
                dTdz(i,j,k2)=0.0_r8
                tl_dTdz(i,j,k2)=0.0_r8
                FS(i,j,k2)=0.0_r8
                tl_FS(i,j,k2)=0.0_r8
              END DO
            END DO
          ELSE
            DO j=Jstr-1,Jend+1
              DO i=Istr-1,Iend+1
                cff=1.0_r8/(z_r(i,j,k+1)-                               &
     &                      z_r(i,j,k  ))
                tl_cff=-cff*cff*(tl_z_r(i,j,k+1)-                       &
     &                           tl_z_r(i,j,k  ))
                dTdz(i,j,k2)=cff*(LapT(i,j,k+1)-                        &
     &                            LapT(i,j,k  ))
                tl_dTdz(i,j,k2)=tl_cff*(LapT(i,j,k+1)-                  &
     &                                  LapT(i,j,k  ))+                 &
     &                          cff*(tl_LapT(i,j,k+1)-                  &
     &                               tl_LapT(i,j,k  ))
              END DO
            END DO
          END IF
!
!  Compute components of the rotated tracer flux (T m4/s) along
!  geopotential surfaces.
!
          IF (k.gt.0) THEN
            DO j=Jstr,Jend
              DO i=Istr,Iend+1
                cff=0.25_r8*(diff4(i,j,itrc)+diff4(i-1,j,itrc))*        &
     &              on_u(i,j)
!>              FX(i,j)=cff*
!>   &                  (Hz(i,j,k)+Hz(i-1,j,k))*                        &
!>   &                  (dTdx(i  ,j,k1)-                                &
!>   &                   0.5_r8*(MIN(dZdx(i,j,k1),0.0_r8)*              &
!>   &                              (dTdz(i-1,j,k1)+                    &
!>   &                               dTdz(i  ,j,k2))+                   &
!>   &                           MAX(dZdx(i,j,k1),0.0_r8)*              &
!>   &                              (dTdz(i-1,j,k2)+                    &
!>   &                               dTdz(i  ,j,k1))))
!>
                tl_FX(i,j)=cff*                                         &
     &                     ((tl_Hz(i,j,k)+tl_Hz(i-1,j,k))*              &
     &                      (dTdx(i,j,k1)-                              &
     &                       0.5_r8*(MIN(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i-1,j,k1)+                &
     &                                   dTdz(i  ,j,k2))+               &
     &                               MAX(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i-1,j,k2)+                &
     &                                   dTdz(i  ,j,k1))))+             &
     &                      (Hz(i,j,k)+Hz(i-1,j,k))*                    &
     &                      (tl_dTdx(i,j,k1)-                           &
     &                       0.5_r8*(MIN(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i-1,j,k1)+             &
     &                                   tl_dTdz(i  ,j,k2))+            &
     &                               MAX(dZdx(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i-1,j,k2)+             &
     &                                   tl_dTdz(i  ,j,k1)))-           &
     &                       0.5_r8*((0.5_r8+                           &
     &                                SIGN(0.5_r8,-dZdx(i,j,k1)))*      &
     &                               tl_dZdx(i,j,k1)*                   &
     &                               (dTdz(i-1,j,k1)+dTdz(i,j,k2))+     &
     &                               (0.5_r8+                           &
     &                                SIGN(0.5_r8, dZdx(i,j,k1)))*      &
     &                               tl_dZdx(i,j,k1)*                   &
     &                               (dTdz(i-1,j,k2)+dTdz(i,j,k1)))))
              END DO
            END DO
            DO j=Jstr,Jend+1
              DO i=Istr,Iend
                cff=0.25_r8*(diff4(i,j,itrc)+diff4(i,j-1,itrc))*        &
     &              om_v(i,j)
!>              FE(i,j)=cff*                                            &
!>   &                  (Hz(i,j,k)+Hz(i,j-1,k))*                        &
!>   &                  (dTde(i,j,k1)-                                  &
!>   &                   0.5_r8*(MIN(dZde(i,j,k1),0.0_r8)*              &
!>   &                              (dTdz(i,j-1,k1)+                    &
!>   &                               dTdz(i,j  ,k2))+                   &
!>   &                           MAX(dZde(i,j,k1),0.0_r8)*              &
!>   &                              (dTdz(i,j-1,k2)+                    &
!>   &                               dTdz(i,j  ,k1))))
!>
                tl_FE(i,j)=cff*                                         &
     &                     ((tl_Hz(i,j,k)+tl_Hz(i,j-1,k))*              &
     &                      (dTde(i,j,k1)-                              &
     &                       0.5_r8*(MIN(dZde(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i,j-1,k1)+                &
     &                                   dTdz(i,j  ,k2))+               &
     &                               MAX(dZde(i,j,k1),0.0_r8)*          &
     &                                  (dTdz(i,j-1,k2)+                &
     &                                   dTdz(i,j  ,k1))))+             &
     &                      (Hz(i,j,k)+Hz(i,j-1,k))*                    &
     &                      (tl_dTde(i,j,k1)-                           &
     &                       0.5_r8*(MIN(dZde(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i,j-1,k1)+             &
     &                                   tl_dTdz(i,j  ,k2))+            &
     &                               MAX(dZde(i,j,k1),0.0_r8)*          &
     &                                  (tl_dTdz(i,j-1,k2)+             &
     &                                   tl_dTdz(i,j  ,k1)))-           &
     &                       0.5_r8*((0.5_r8+                           &
     &                                SIGN(0.5_r8,-dZde(i,j,k1)))*      &
     &                               tl_dZde(i,j,k1)*                   &
     &                               (dTdz(i,j-1,k1)+dTdz(i,j,k2))+     &
     &                               (0.5_r8+                           &
     &                                SIGN(0.5_r8, dZde(i,j,k1)))*      &
     &                               tl_dZde(i,j,k1)*                   &
     &                               (dTdz(i,j-1,k2)+dTdz(i,j,k1)))))
              END DO
            END DO
            IF (k.lt.N(ng)) THEN
              DO j=Jstr,Jend
                DO i=Istr,Iend
                  cff=0.5_r8*diff4(i,j,itrc)
                  cff1=MIN(dZdx(i  ,j,k1),0.0_r8)
                  cff2=MIN(dZdx(i+1,j,k2),0.0_r8)
                  cff3=MAX(dZdx(i  ,j,k2),0.0_r8)
                  cff4=MAX(dZdx(i+1,j,k1),0.0_r8)
                  tl_cff1=(0.5_r8+SIGN(0.5_r8,-dZdx(i  ,j,k1)))*        &
     &                    tl_dZdx(i  ,j,k1)
                  tl_cff2=(0.5_r8+SIGN(0.5_r8,-dZdx(i+1,j,k2)))*        &
     &                    tl_dZdx(i+1,j,k2)
                  tl_cff3=(0.5_r8+SIGN(0.5_r8, dZdx(i  ,j,k2)))*        &
     &                    tl_dZdx(i  ,j,k2)
                  tl_cff4=(0.5_r8+SIGN(0.5_r8, dZdx(i+1,j,k1)))*        &
     &                    tl_dZdx(i+1,j,k1)
!>
!>                FS(i,j,k2)=cff*                                       &
!>   &                       (cff1*(cff1*dTdz(i,j,k2)-                  &
!>   &                              dTdx(i  ,j,k1))+                    &
!>   &                        cff2*(cff2*dTdz(i,j,k2)-                  &
!>   &                              dTdx(i+1,j,k2))+                    &
!>   &                        cff3*(cff3*dTdz(i,j,k2)-                  &
!>   &                              dTdx(i  ,j,k2))+                    &
!>   &                        cff4*(cff4*dTdz(i,j,k2)-                  &
!>   &                              dTdx(i+1,j,k1)))
!>
                  tl_FS(i,j,k2)=cff*                                    &
     &                          (tl_cff1*(cff1*dTdz(i,j,k2)-            &
     &                                    dTdx(i  ,j,k1))+              &
     &                           tl_cff2*(cff2*dTdz(i,j,k2)-            &
     &                                    dTdx(i+1,j,k2))+              &
     &                           tl_cff3*(cff3*dTdz(i,j,k2)-            &
     &                                    dTdx(i  ,j,k2))+              &
     &                           tl_cff4*(cff4*dTdz(i,j,k2)-            &
     &                                    dTdx(i+1,j,k1))+              &
     &                           cff1*(tl_cff1*dTdz(i,j,k2)+            &
     &                                 cff1*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i  ,j,k1))+              &
     &                           cff2*(tl_cff2*dTdz(i,j,k2)+            &
     &                                 cff2*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i+1,j,k2))+              &
     &                           cff3*(tl_cff3*dTdz(i,j,k2)+            &
     &                                 cff3*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i  ,j,k2))+              &
     &                           cff4*(tl_cff4*dTdz(i,j,k2)+            &
     &                                 cff4*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTdx(i+1,j,k1)))
!
                  cff1=MIN(dZde(i,j  ,k1),0.0_r8)
                  cff2=MIN(dZde(i,j+1,k2),0.0_r8)
                  cff3=MAX(dZde(i,j  ,k2),0.0_r8)
                  cff4=MAX(dZde(i,j+1,k1),0.0_r8)
                  tl_cff1=(0.5_r8+SIGN(0.5_r8,-dZde(i,j  ,k1)))*        &
     &                    tl_dZde(i,j  ,k1)
                  tl_cff2=(0.5_r8+SIGN(0.5_r8,-dZde(i,j+1,k2)))*        &
     &                    tl_dZde(i,j+1,k2)
                  tl_cff3=(0.5_r8+SIGN(0.5_r8, dZde(i,j  ,k2)))*        &
     &                    tl_dZde(i,j  ,k2)
                  tl_cff4=(0.5_r8+SIGN(0.5_r8, dZde(i,j+1,k1)))*        &
     &                    tl_dZde(i,j+1,k1)
!>                FS(i,j,k2)=FS(i,j,k2)+                                &
!>   &                       cff*                                       &
!>   &                       (cff1*(cff1*dTdz(i,j,k2)-                  &
!>   &                              dTde(i,j  ,k1))+                    &
!>   &                        cff2*(cff2*dTdz(i,j,k2)-                  &
!>   &                              dTde(i,j+1,k2))+                    &
!>   &                        cff3*(cff3*dTdz(i,j,k2)-                  &
!>   &                              dTde(i,j  ,k2))+                    &
!>   &                        cff4*(cff4*dTdz(i,j,k2)-                  &
!>   &                              dTde(i,j+1,k1)))
!>
                  tl_FS(i,j,k2)=tl_FS(i,j,k2)+                          &
     &                          cff*                                    &
     &                          (tl_cff1*(cff1*dTdz(i,j,k2)-            &
     &                                    dTde(i,j  ,k1))+              &
     &                           tl_cff2*(cff2*dTdz(i,j,k2)-            &
     &                                    dTde(i,j+1,k2))+              &
     &                           tl_cff3*(cff3*dTdz(i,j,k2)-            &
     &                                    dTde(i,j  ,k2))+              &
     &                           tl_cff4*(cff4*dTdz(i,j,k2)-            &
     &                                    dTde(i,j+1,k1))+              &
     &                           cff1*(tl_cff1*dTdz(i,j,k2)+            &
     &                                 cff1*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j  ,k1))+              &
     &                           cff2*(tl_cff2*dTdz(i,j,k2)+            &
     &                                 cff2*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j+1,k2))+              &
     &                           cff3*(tl_cff3*dTdz(i,j,k2)+            &
     &                                 cff3*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j  ,k2))+              &
     &                           cff4*(tl_cff4*dTdz(i,j,k2)+            &
     &                                 cff4*tl_dTdz(i,j,k2)-            &
     &                                 tl_dTde(i,j+1,k1)))
                END DO
              END DO
            END IF
!
!  Time-step biharmonic, geopotential diffusion term (m Tunits).
!
            DO j=Jstr,Jend
              DO i=Istr,Iend
!>              cff=dt(ng)*pm(i,j)*pn(i,j)*                             &
!>   &                     (FX(i+1,j  )-FX(i,j)+                        &
!>   &                      FE(i  ,j+1)-FE(i,j))+                       &
!>   &              dt(ng)*(FS(i,j,k2)-FS(i,j,k1))
!>
                tl_cff=dt(ng)*pm(i,j)*pn(i,j)*                          &
     &                        (tl_FX(i+1,j)-tl_FX(i,j)+                 &
     &                         tl_FE(i,j+1)-tl_FE(i,j))+                &
     &                 dt(ng)*(tl_FS(i,j,k2)-tl_FS(i,j,k1))
!>              t(i,j,k,nnew,itrc)=t(i,j,k,nnew,itrc)-cff
!>
                tl_t(i,j,k,nnew,itrc)=tl_t(i,j,k,nnew,itrc)-tl_cff
#ifdef TS_MPDATA_NOT_YET
                cff1=1.0_r8/Hz(i,j,k)
                tl_cff1=-cff1*cff1*tl_Hz(i,j,k)
!>              t(i,j,k,3,itrc)=cff1*t(i,j,k,nnew,itrc)
!>
                tl_t(i,j,k,3,itrc)=tl_cff1*t(i,j,k,nnew,itrc)+          &
     &                             cff1*tl_t(i,j,k,nnew,itrc)
#endif
#ifdef DIAGNOSTICS_TS
!!              DiaTwrk(i,j,k,itrc,iThdif)=-cff
#endif
              END DO
            END DO
          END IF
        END DO K_LOOP2
      END DO T_LOOP
#undef I_RANGE
#undef J_RANGE
      RETURN
      END SUBROUTINE tl_t3dmix4_tile
