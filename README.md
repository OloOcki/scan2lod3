# Scan2LoD3
Implementation of the CVPR paper "Scan2LoD3: Reconstructing semantic 3D building models at LoD3 using ray casting and Bayesian networks"

<p float="center">
    <img src="https://github.com/OloOcki/tum-facade/blob/main/img/frontFigure.png" width="95%" title="frontFigure"/>
</p>

Scan2LoD3: Our method reconstructs detailed semantic 3D building models; Its backbone is laser rays’ physics providing geometrical cues enhancing semantic segmentation accuracy.

[Project's website](https://sites.google.com/view/olafwysocki/papers/scan2lod3) [**tum2twin** benchmark](https://github.com/tum-gis/tum2twin)

## Highlights
**BEFORE scan2lod3: LoD2**
![](https://github.com/OloOcki/scan2lod3/blob/main/img/lod2.gif)

![](https://github.com/OloOcki/scan2lod3/blob/main/img/LoD3reconstructed.gif)
**AFTER scan2lod3: LoD3**

Our approach to visibility analysis:
![](https://github.com/OloOcki/scan2lod3/blob/main/img/rayCasting.gif)
Visibility analysis using laser scanning observations and 3D models on a voxel grid. The ray is traced from the sensor position si to the hit point pi. 
The voxel is: empty if the ray traverses it; occupied when it contains pi; unknown if unmeasured; confirmed when occupied voxel intersects with vector plane; and conflicted when the plane intersects with an empty voxel.



## Implementation overview

The implementation can be divided into several steps:
1. Ray casting (C++) 
2. Bayesian network, fusion (R)

*full overview - pending*

## Paper

For the in-depth conept understanding do not hesitate to check out the paper:

```plain
@article{scan2lod3Wysockietal,
title = {Scan2LoD3: Reconstructing semantic 3D building models at LoD3 using ray casting and Bayesian networks},
journal = {International Journal of Applied Earth Observation and Geoinformation},
author = {Wysocki, O., Xia, Y., Wysocki M., Grilli, E., Hoegner, L., Cremers D., and Stilla, U.},
keywords = {MLS point clouds, Building reconstruction, Semantic 3D building models, Underpasses, Buildings refinement, Bayesian networks, Uncertainty},
}
```

## Data

Small sample dataset it attached to this repo: \raycasting\examples. For the vector objects and point cloud please check the [**tum2twin**](https://github.com/tum-gis/tum2twin) benchmark dataset.

## Contact details

Should you have any further questions do not hesitate to ask me: olaf.wysocki@tum.de
