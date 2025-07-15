#include <iostream>
#include "14281.h"

std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}


int main()
{
    std::string input_string;
    std::cin >> input_string;

    Codec** CodecPtr = new Codec*[2];

    CodecPtr[0] = getCodec("Dummy",input_string);
    encode_decode(*CodecPtr[0]);
    std::cout << "Dummy encoding: ";
    std::cout << *CodecPtr[0] << std::endl;
    encode_decode(*CodecPtr[0]);
    std::cout << "Dummy decoding: ";
    std::cout << *CodecPtr[0] << std::endl;

    CodecPtr[1] = getCodec("RLE",input_string);
    encode_decode(*CodecPtr[1]);
    std::cout << "RLE encoding: ";
    std::cout << *CodecPtr[1] << std::endl;
    encode_decode(*CodecPtr[1]);
    std::cout << "RLE decoding: ";
    std::cout << *CodecPtr[1] << std::endl;

    delete CodecPtr[0];
    delete CodecPtr[1];
    delete [] CodecPtr;
}
