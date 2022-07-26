//
// Created by layetri on 7/25/22.
//

#ifndef	SHIFTJISREADER_H
#define SHIFTJISREADER_H

#include <juce_core/juce_core.h>
#include <fstream>
#include <iconv.h>

class ShiftJIS {
    public:
        /**
         * Convert a file from ShiftJIS to UTF-8 encoding
         * @param file an instance of juce::File to convert
         * @return the file's contents as a juce::StringArray
         */
        static juce::StringArray read(const juce::File& file) {
            juce::StringArray lines;

            if(file.exists()) {
                std::fstream filestream(file.getFullPathName().toStdString());
                std::string res;
                char sDst[1024];

                while(getline(filestream, res)) {
                    auto nSrc = std::strlen(res.c_str());
                    auto pSrc = res.c_str();
                    size_t nDst = 1023;
                    iconv_t icd;
                    char* pDst = sDst;

                    while(0 < nSrc) {
                        icd = iconv_open("UTF-8", "Shift_JIS");
                        iconv(icd, const_cast<char **>(&pSrc), &nSrc, &pDst, &nDst);
                        iconv_close(icd);
                    }

		            juce::String str = juce::CharPointer_UTF8(sDst);
                    str = str.upToFirstOccurrenceOf("\r", false, true);

                    lines.add(str);
                    res = "";
                }
            } else {
                std::cerr << "[ShiftJIS] File does not exist!\n";
            }

            return lines;
        }
};

#endif //SHIFTJISREADER_H
