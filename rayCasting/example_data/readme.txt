1. The files are transformed to UTM32N CRS from ASCII files of TUM Dataset 2016 in ENU CRS
2. The respective shift is applied to assure correct precision of points AND view points coordinates, the shift is hard-coded: 
	shiftX, shiftY, shiftZ = 690729.0567, 5335897.0603, 500
3. x,y,z (local position of points), vp_x, vp_y, vp_z (scanner origin)
