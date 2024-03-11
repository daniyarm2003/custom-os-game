#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

bool write_image_source(const fs::path& imagePath, std::vector<std::string>& imageStructs, fs::path& headerPath) {
    int width, height, numChannels;

    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &numChannels, 0);

    if(data == NULL) {
        return false;
    }

    else if(numChannels != 3 && numChannels != 4) {
        stbi_image_free(data);
        return false;
    }

    std::string structName = imagePath.stem().string() + "_image_data";

    fs::path sourcePath = imagePath.parent_path() / imagePath.stem().concat(".c");

    std::ofstream srcWriter(sourcePath, std::ios::trunc);
    srcWriter.exceptions(std::ofstream::badbit | std::ofstream::failbit);

    try {
        srcWriter << "#include " << "\"./" << headerPath.filename().string() << "\"\n\n";
        srcWriter << "Image " << structName << " = {\n";
        srcWriter << "\t" << width << ", " << height << ", " << (numChannels == 3 ? "BYTES_PER_PIXEL_RGB" : "BYTES_PER_PIXEL_RGBA") << ",\n";

        int bytesPerLine = 16 * numChannels;

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                int numBytes = (y * width + x) * numChannels;
                int numBytesInLine = numBytes % bytesPerLine;

                if(numBytesInLine == 0) {
                    srcWriter << "\t\"";
                }

                for(int i = 0; i < numChannels; i++) {
                    srcWriter << "\\x" << std::hex << +data[numBytes + i];
                }

                if(numBytesInLine == bytesPerLine - numChannels || numBytes == (width * height - 1) * numChannels) {
                    srcWriter << "\"\n";
                }
            }
        }

        srcWriter << "};";
        srcWriter.close();
    }
    catch(std::ofstream::failure& ex) {
        std::cerr << "Failed writing to " << sourcePath << " due to error: " << ex.what() << "\n";

        stbi_image_free(data);
        return false;
    }

    imageStructs.push_back(structName);

    stbi_image_free(data);
    return true;
}

bool write_image_header(const fs::path& headerPath, const std::vector<std::string>& imageStructs) {
    std::ofstream headerWriter(headerPath, std::ios::trunc);
    headerWriter.exceptions(std::ofstream::failbit | std::ofstream::badbit);

    try {
        headerWriter << "#include \"../graphics/image.h\"\n\n";
        
        for(const auto& structName : imageStructs) {
            headerWriter << "extern Image " << structName << ";\n";
        }
    }
    catch(std::ofstream::failure& ex) {
        std::cerr << "Failed writing to " << headerPath << " due to error: " << ex.what() << "\n";
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <image directory> <output file>" << std::endl;
        return 1;
    }

    fs::path imageDir(argv[1]);
    fs::path headerPath = imageDir / argv[2];

    if(!fs::exists(imageDir) || !fs::is_directory(imageDir)) {
        std::cerr << "ERROR: " << imageDir << " is not a directory" << std::endl;
        return 1;
    }

    std::unordered_set<std::string> supportedImageTypes;
    std::vector<std::string> imageStructs;

    supportedImageTypes.emplace(".png");
    supportedImageTypes.emplace(".jpg");
    supportedImageTypes.emplace(".gif");

    for(const auto& dirEntry : fs::directory_iterator(imageDir)) {
        const fs::path& entryPath = dirEntry.path();

        if(!entryPath.has_extension() || !supportedImageTypes.contains(entryPath.extension())) {
            continue;
        }

        if(!write_image_source(entryPath, imageStructs, headerPath)) {
            std::cerr << "Unable to convert file " << entryPath << " due to error\n" << std::endl;
            return 1;
        }
    }

    if(!write_image_header(headerPath, imageStructs)) {
        std::cerr << "Unable to write header file" << std::endl;
        return 1;
    }
}