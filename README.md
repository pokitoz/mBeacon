# mBeacon

## Antenna

- No angle on the trace
- Vias should surround the track and the antenna to apply a shielding
- It is best to avoid the use FR4 stack layer
  - As this is not controled and epsilon can vary. 
  - HR370 isola is better to control the impedence

To check the 50Ohm, use the too AppCAD or https://saturnpcb.com/saturn-pcb-toolkit/
- Go to `Tools > DRC...` 
- find layer stack in eagle..
- copper is selected when ordering. Check the manufacturer webite: https://jlcpcb.com/capabilities/Capabilities
- stack manager: Isolation height and copper height Track height.

## Manufacturing

- File > Generate CAM data
  - Export to .zip and upload to manufacturing site
- For jlcpcb, BOM and CPL needs to be generated: https://support.jlcpcb.com/article/132-how-to-generate-bom-and-cpl-from-eagle-cad-automatically
