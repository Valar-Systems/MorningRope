# What's new in v1.1
The current hardware revision is **v1.1**. Print from [`hardware/plastics/v1.1`](plastics/v1.1) (the [v1.0](plastics/v1.0) files remain for anyone who already built one).

- **Stronger pull (11 lb → 15 lb)** — a smaller-diameter **MK8** drive gear replaces the MK7.
- **Fewer parts** — each arm now uses **one larger 633ZZ bearing (3 × 13 × 5 mm)** instead of two small bearings.
- **Pre-cut PTFE tubes** — tubes now ship pre-cut to **10 / 40 / 70 mm** (two of each), so there's no measuring or razor-cutting during the build.

The plastics changed slightly to suit the new tube lengths; otherwise assembly is the same.

## Ceiling mounting for top mounted curtains

For curtains on a ceiling-mounted track, print these two v1.2.2 parts in place of the standard pulley bottom and rope elbow top:

- [End pulley bottom ceiling mount](plastics/v1.2.2/curtain/end-pulley-bottom-ceiling-mount.step)
- [Rope elbow top ceiling mount](plastics/v1.2.2/curtain/rope-elbow-top-ceiling-mount.step)

Print a matching spacer for each mount. Choose a thickness that positions the rope level with your curtain carriages. The [spacer generator](plastics/v1.2.2/curtain/make_mount_spacers.py) creates both spacer models as STEP and STL files; it needs Python with CadQuery installed. From the repository root, run for example:

```sh
python hardware/plastics/v1.2.2/curtain/make_mount_spacers.py 40mm
```

This writes `end-pulley-ceiling-spacer-40mm.step` / `.stl` and `rope-elbow-ceiling-spacer-40mm.step` / `.stl` in the curtain parts folder. You can also pass an inch value such as `1.5in`; omitting the value defaults to `1.5in`. If the two mounts need different spacer thicknesses, run the generator once for each size and print the matching spacer from each run.

The holes were sized for #9 screws: 4.7 mm through the ceiling mounts and 5.0 mm through the spacers.

Place each spacer between its mount and the ceiling. Screw the mounts through the spacers into ceiling framing (joists or studs); we recommend fastening into framing rather than drywall alone. Use screws long enough to reach the framing after passing through the mount and spacer.

You may need to flip the carriages around to reach the screws that secure the rope, then route the rope "backwards" relative to the standard installation so you can screw it into the carriages.

# Instructions
Image build guide can be found [here](https://canva.link/tmpoyau5pfkddx3).\
Video build guide can be found [here](https://youtu.be/uowt6jLxNso).\
Video installation guide can be found [here](https://youtu.be/p8078ezLZHw).

# Parts
You can purchase a kit [here](https://valarsystems.com/products/ropener) that includes all of these parts.\
Or you can source the parts below.

| Item  | Quantity|
| --------|-------|
| [PCB](https://valarsystems.com/products/val3000)|1|
| [Motor](https://valarsystems.com/products/stepper-motor-nema-17)|1|
| [24V 1.5A Power adapter](https://valarsystems.com/products/power-adapter)|1|
| [Cable extension](https://valarsystems.com/products/barrel-plug-extension-cable?variant=43389605609531)|As needed|
| [3M Command Strips](https://valarsystems.com/products/3m-command-strips)|4|
| [Rope](https://valarsystems.com/products/rope)|30ft|
| [PTFE Tubing (pre-cut: 2×10mm, 2×40mm, 2×70mm)](https://valarsystems.com/products/ptfe-tube)|6|
| [M3 Square Nut](https://valarsystems.com/products/m3-square-nut)|4|
| [M3x35mm Button Head Screw](https://valarsystems.com/products/m3-x-35mm-button-head-screw)|3|
| [V-Groove Pulley](https://valarsystems.com/products/v-groove-pulley)|1|
| [M3x10mm Flat Head Screw](https://valarsystems.com/products/m3-x-35mm-button-head-screw-copy)|2|
| [M3x15mm Button Head Screw](https://valarsystems.com/products/m3-x-10mm-thread-forming-screw-copy)|3|
| [633ZZ Bearing (3×13×5mm)](https://valarsystems.com/products/bearing)|2|
| [MK8 Drive Gear](https://valarsystems.com/products/ropener-drive-gear)|1|
| [Zip Tie](https://valarsystems.com/products/zip-tie)|4|
| [M3x10mm Thread Forming Screw](https://valarsystems.com/products/m3-x-10mm-thread-forming-screw)|23|
