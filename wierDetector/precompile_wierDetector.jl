using .WierDetector


#push!(ARGS, "arg")
global input_dir = "input_data/"
global output_dir = "output_data/"

WierDetector.julia_main()

list_deps = [
    "ArgParse",
    "FileIO",
    "Images",
    "Statistics",
    "Printf",
]

# using PackageCompiler
# create_sysimage(list_deps, sysimage_path="wier_sys.so", precompile_execution_file="precompile_wierDetector.jl")