/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Baskerville_ttc;
    const int            Baskerville_ttcSize = 1371312;

    extern const char*   Courier_New_ttf;
    const int            Courier_New_ttfSize = 684624;

    extern const char*   orc_png;
    const int            orc_pngSize = 299549;

    extern const char*   gnoll_png;
    const int            gnoll_pngSize = 275706;

    extern const char*   goblin_png;
    const int            goblin_pngSize = 249079;

    extern const char*   dnd_logo_png;
    const int            dnd_logo_pngSize = 426629;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
