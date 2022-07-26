## ShiftJIS for JUCE
A single-header tool for converting files from ShiftJIS to UTF-8 encoding.

#### Why?
The Japanese singing synth UTAU uses ShiftJIS encoding on all its files, so
in order to use UTAU files with JUCE, I needed a compatibility layer.

#### How to use
It's super-duper ultra simple. Just include the header file in your `cpp` file. It contains a single method `read`, that can be called statically:
```juce::StringArray lines = ShiftJIS::read(juce::File& file_to_convert);```

It depends on `iconv` for the conversion, so make sure this library is installed! (Windows users beware...)
