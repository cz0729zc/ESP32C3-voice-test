import sys
import os

def convert_file_to_c_array(input_file, output_file, array_name):
    """
    Converts a binary file to a C header file containing a uint8_t array.
    """
    try:
        with open(input_file, 'rb') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Error: Input file '{input_file}' not found.")
        return

    c_code = f"// Converted from {os.path.basename(input_file)}\n"
    c_code += f"#ifndef _{array_name.upper()}_H_\n"
    c_code += f"#define _{array_name.upper()}_H_\n\n"
    c_code += "#include <stdint.h>\n\n"
    c_code += f"const uint8_t {array_name}[] = {{\n    "

    line_len = 0
    for byte in content:
        hex_val = f"0x{byte:02x}, "
        if line_len + len(hex_val) > 80:
            c_code += "\n    "
            line_len = 0
        c_code += hex_val
        line_len += len(hex_val)

    c_code = c_code.rstrip(", ") + "\n};\n\n"
    c_code += f"#endif // _{array_name.upper()}_H_\n"

    with open(output_file, 'w') as f:
        f.write(c_code)

    print(f"Successfully converted '{input_file}' to '{output_file}'.")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python json2c.py <input_file> <output_file> <array_name>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]
    c_array_name = sys.argv[3]

    convert_file_to_c_array(input_path, output_path, c_array_name)