#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00010003
#define MULTIBOOT_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

__attribute__((section(".multiboot")))
const unsigned long multiboot_header[] = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_CHECKSUM,
    0,
    0
};

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define YELLOW 0x0E
#define RED 0x04

unsigned short *terminal_buffer;
int vga_index;

void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            terminal_buffer[index] = (unsigned short) ' ' | (unsigned short) YELLOW << 8;
        }
    }
}

void print_string(const char *str, unsigned char color) {
    int index = 0;
    while (str[index]) {
        terminal_buffer[vga_index] = (unsigned short)str[index] | (unsigned short)color << 8;
        index++;
        vga_index++;
    }
}

void main(void) {
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_index = 0;

    clear_screen();
    print_string("Hello, World!", YELLOW);
    vga_index = VGA_WIDTH;    /* next line */
    print_string("Kernel is running!", RED);

    while (1) {
        // Halt the CPU
        __asm__ __volatile__("hlt");
    }
}