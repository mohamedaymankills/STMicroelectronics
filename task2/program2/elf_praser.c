/************************* Arth    : Mohamed Ayman *************************/
/************************* file    : ST Task 2     *************************/
/************************* version : 0.0.1         *************************/
/************************* date    : 19 - 7 - 2024 *************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define the ELF header structure for 64-bit ELF files
typedef struct {
    unsigned char e_ident[16]; // ELF Identification
    uint16_t e_type;           // Object file type
    uint16_t e_machine;        // Machine type
    uint32_t e_version;        // Object file version
    uint64_t e_entry;          // Entry point address
    uint64_t e_phoff;          // Program header offset
    uint64_t e_shoff;          // Section header offset
    uint32_t e_flags;          // Processor-specific flags
    uint16_t e_ehsize;         // ELF header size
    uint16_t e_phentsize;      // Size of program header entry
    uint16_t e_phnum;          // Number of program header entries
    uint16_t e_shentsize;      // Size of section header entry
    uint16_t e_shnum;          // Number of section header entries
    uint16_t e_shstrndx;       // Section name string table index
} ELFHeader64;

const char* get_osabi_name(unsigned char osabi) {
    switch(osabi) {
        case 0: return "UNIX - System V";
        case 1: return "UNIX - HP-UX";
        case 2: return "UNIX - NetBSD";
        case 3: return "UNIX - GNU";
        case 6: return "UNIX - Solaris";
        case 7: return "UNIX - AIX";
        case 8: return "UNIX - IRIX";
        case 9: return "UNIX - FreeBSD";
        case 10: return "UNIX - TRU64";
        case 11: return "Novell - Modesto";
        case 12: return "UNIX - OpenBSD";
        case 13: return "VMS - OpenVMS";
        case 14: return "HP - Non-Stop Kernel";
        case 15: return "AROS";
        case 16: return "FenixOS";
        case 17: return "Nuxi CloudABI";
        case 18: return "Stratus Technologies OpenVOS";
        default: return "Unknown";
    }
}

const char* get_type_name(uint16_t type) {
    switch(type) {
        case 0: return "No file type";
        case 1: return "Relocatable file";
        case 2: return "Executable file";
        case 3: return "DYN (Position-Independent Executable file)";
        case 4: return "Core file";
        default: return "Unknown";
    }
}

const char* get_machine_name(uint16_t machine) {
    switch(machine) {
        case 0: return "No machine";
        case 2: return "SPARC";
        case 3: return "x86";
        case 6: return "MIPS";
        case 7: return "Intel 80860";
        case 8: return "MIPS RS3000";
        case 10: return "ARM";
        case 40: return "ARM 64-bit";
        case 62: return "Advanced Micro Devices X86-64";
        case 183: return "AArch64";
        case 19: return "Advanced Micro Devices (AMD)";
        default: return "Unknown";
    }
}

void print_elf_header(ELFHeader64 *header) {
    printf("Magic:                             ");
    for(int i = 0; i < 16; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");

    printf("Class:                             ");
    switch(header->e_ident[4]) {
        case 1: printf("ELF32\n"); break;
        case 2: printf("ELF64\n"); break;
        default: printf("Invalid class\n"); break;
    }

    printf("Data:                              ");
    switch(header->e_ident[5]) {
        case 1: printf("2's complement, little endian\n"); break;
        case 2: printf("2's complement, big endian\n"); break;
        default: printf("Invalid data encoding\n"); break;
    }

    printf("Version:                           %d (current)\n", header->e_ident[6]);
    printf("OS/ABI:                            %s\n", get_osabi_name(header->e_ident[7]));
    printf("ABI Version:                       %d\n", header->e_ident[8]);
    printf("Type:                              %s\n", get_type_name(header->e_type));
    printf("Machine:                           %s\n", get_machine_name(header->e_machine));
    printf("Version:                           0x%x\n", header->e_version);
    printf("Entry point address:               0x%lx\n", header->e_entry);
    printf("Start of program headers:          %lu (bytes into file)\n", header->e_phoff);
    printf("Start of section headers:          %lu (bytes into file)\n", header->e_shoff);
    printf("Flags:                             0x%x\n", header->e_flags);
    printf("Size of this header:               %u (bytes)\n", header->e_ehsize);
    printf("Size of program headers:           %u (bytes)\n", header->e_phentsize);
    printf("Number of program headers:         %u\n", header->e_phnum);
    printf("Size of section headers:           %u (bytes)\n", header->e_shentsize);
    printf("Number of section headers:         %u\n", header->e_shnum);
    printf("Section header string table index: %u\n", header->e_shstrndx);
}

int main() {
    char file_path[256];
    printf("Enter the path to the ELF file: ");
    scanf("%255s", file_path);

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    ELFHeader64 header;
    if (fread(&header, sizeof(header), 1, file) != 1) {
        perror("Error reading ELF header");
        fclose(file);
        return 1;
    }

    print_elf_header(&header);

    fclose(file);
    return 0;
}

