import os

def file_to_array(file_path):
    with open(file_path, 'r') as infile:
        lines = infile.readlines()
    return lines

def replace_includes_from_array_to_file(lines, output_file):
    with open(output_file, 'w') as outfile:
        for line in lines:
            if line.strip().startswith("#include"):
                include_file = line.strip().split('"')[1]
                include_full_path = os.path.join(include_path, include_file)
                if os.path.exists(include_full_path):
                    with open(include_full_path, 'r') as incfile:
                        outfile.write(incfile.read())
                        outfile.write("\n")
                else:
                    raise FileNotFoundError(f"Included file {include_file} not found.")
            else:
                outfile.write(line)

def compile(input_file, output_file, include_path):
    lines = file_to_array(input_file)
    replace_includes_from_array_to_file(lines, output_file)

compile("shaders/main.glsl", "shaders/compiled_shader.glsl", "shaders/")
