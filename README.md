# :rotating_light: Scan2LoD3 :cityscape:
Implementation of the CVPR '23 paper: 

"Scan2LoD3: Reconstructing semantic 3D building models at LoD3 using ray casting and Bayesian networks"

<p align="center">
    <img src="https://github.com/OloOcki/scan2lod3/blob/main/img/frontFigure.png" width="40%" title="frontFigure"/>
</p>

Scan2LoD3: Our method reconstructs detailed semantic 3D building models; Its backbone is laser rays’ physics providing geometrical cues enhancing semantic segmentation accuracy.

[<img src="https://github.com/OloOcki/scan2lod3/blob/main/img/paper.png" width="120"/>](https://sites.google.com/view/olafwysocki/papers/scan2lod3)
[<img src="https://github.com/OloOcki/scan2lod3/blob/main/img/website.png" width="120"/>](https://sites.google.com/view/olafwysocki/papers/scan2lod3)
[<img src="https://github.com/OloOcki/scan2lod3/blob/main/img/data.png" width="120"/>](https://sites.google.com/view/olafwysocki/papers/scan2lod3) 

## :star2: Highlights :star2:
<p align="center">
    <img src="https://github.com/OloOcki/scan2lod3/blob/main/img/gist.png" width="100%" title="frontFigure"/>
</p>

The workflow of the proposed Scan2LoD3 consists of three parallel branches: 
 - The first is generating the point cloud probability map based on a modified Point Transformer network (top); 
- the second is producing a conflicts probability map from the visibility of the laser scanner in conjunction with a 3D building model (middle); 
- and the third is using Mask-RCNN to obtain a texture probability map from 2D images. 
We then fuse three probability maps with a Bayesian network to obtain the final facade-level segmentation, enabling a CityGML-compliant LoD3 building model reconstruction.


### :-1: **BEFORE scan2lod3: LoD2**
![](https://github.com/OloOcki/scan2lod3/blob/main/img/lod2.gif)
### :+1: **AFTER scan2lod3: LoD3**
![](https://github.com/OloOcki/scan2lod3/blob/main/img/LoD3reconstructed.gif)


### :mag_right: Our approach to visibility analysis:
![](https://github.com/OloOcki/scan2lod3/blob/main/img/rayCasting.gif)
Visibility analysis using laser scanning observations and 3D models on a voxel grid. The ray is traced from the sensor position si to the hit point pi. 
The voxel is: empty if the ray traverses it; occupied when it contains pi; unknown if unmeasured; confirmed when occupied voxel intersects with vector plane; and conflicted when the plane intersects with an empty voxel.


## :construction_worker: Implementation overview

The implementation can be divided into several steps:
1. Ray casting (C++)
2. Mask-RCNN (Python)
3. Point Transformer (Python)
4. Confidence estimation; probability map projection; CityGML-compliant 3D modeling (FME)
5. Bayesian network (R)

## :mortar_board: Paper

For the in-depth conept understanding do not hesitate to check out the paper:

```plain
@article{scan2lod3Wysockietal,
title = {Scan2LoD3: Reconstructing semantic 3D building models at LoD3 using ray casting and Bayesian networks},
journal = {International Journal of Applied Earth Observation and Geoinformation},
author = {Wysocki, O., Xia, Y., Wysocki M., Grilli, E., Hoegner, L., Cremers D., and Stilla, U.},
keywords = {MLS point clouds, Building reconstruction, Semantic 3D building models, Underpasses, Buildings refinement, Bayesian networks, Uncertainty},
}
```

## :minidisc: Data

Small sample dataset it attached to this repo: \raycasting\examples. For the vector objects and point cloud please check the [**tum2twin**](https://github.com/tum-gis/tum2twin) benchmark dataset.

## :mailbox: Contact details

Should you have any further questions do not hesitate to ask me: olaf.wysocki@tum.de
