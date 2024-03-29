subroutine forces(npart, x, f, vir, epot, side, rcoff)
  use mod_setprecision
  implicit none
  integer :: npart
  real (kind=dprec) :: x(npart, 3), f(npart, 3)
  real (kind=dprec) :: vir, epot, side, rcoff

  integer :: i, j
  real (kind=dprec) :: rcoffs, sideh, xi, yi, zi, fxi, fyi, fzi, xx, yy, zz 
  real (kind=dprec):: rd, rrd, rrd2, rrd3, rrd4, rrd6, rrd7, r148
  real (kind=dprec):: forcex, forcey, forcez
!     
!     compute forces and accumulate the virial and potential.
!     
  vir = 0.0d0
  epot = 0.0d0
  sideh = 0.5d0*side
  rcoffs = rcoff*rcoff
!
  do i = 1,npart
     xi = x(i,1)
     yi = x(i,2)
     zi = x(i,3)
     fxi = 0.0d0
     fyi = 0.0d0
     fzi = 0.0d0
     do j = i+1,npart

        xx = xi - x(j,1)
        yy = yi - x(j,2)
        zz = zi - x(j,3)
        if (xx < -sideh) xx = xx + side
        if (xx >  sideh) xx = xx - side
        if (yy < -sideh) yy = yy + side
        if (yy >  sideh) yy = yy - side
        if (zz < -sideh) zz = zz + side
        if (zz >  sideh) zz = zz - side
        rd = xx*xx + yy*yy + zz*zz

        if (rd <= rcoffs) then
           rrd = 1.0d0/rd
           rrd3 = rrd*rrd*rrd
           rrd6 = rrd3*rrd3
           r148 = rrd6*rrd - 0.5d0*rrd3*rrd

           epot = epot + (rrd6 - rrd3)
           vir = vir - rd*r148

           fxi = fxi + xx * r148
           fyi = fyi + yy * r148
           fzi = fzi + zz * r148

           f(j,1) = f(j,1) - xx * r148
           f(j,2) = f(j,2) - yy * r148
           f(j,3) = f(j,3) - zz * r148
        endif
     end do
     f(i,1) = f(i,1) + fxi
     f(i,2) = f(i,2) + fyi
     f(i,3) = f(i,3) + fzi
  end do
!
end subroutine forces
