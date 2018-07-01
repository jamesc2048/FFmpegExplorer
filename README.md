An FFmpeg front end to help discover all the cool things FFmpeg is capable of.
Made with QtQuick Controls 2 so should run on Windows, Mac and Linux. Possibly even Android in the future.

The plan is to have nearly everything FFmpeg is capable of exposed and searchable without having to be an expert of the command line interface.

Planned features (not in order):
- Presets
- Batch encodes with preset
- Autopopulate AVOptions from all muxers/codecs and global format/codec context 
- Validation of chosen option ranges
- Preview of planned encode
- Simple and complex filter graphs with interface for settings them through GUI
- Multiple input / output files (complex filtergraphs / -map etc)
- Search functionality with description (E.G. search "brightness" finds "colorlevels" and "eq" filters)
