module WierDetector

#import Pkg
#Pkg.activate(".");

using ArgParse
using FileIO
using Images
using ImageBinarization
using ImageSegmentation
using Statistics

import ImageView

global image_height::Int
global image_width::Int

function parse_cli()
    s = ArgParseSettings()
    @add_arg_table s begin
        "--f"
        help = "Explicitly specify image file. (default = lastest file)"
        arg_type = String
        default = "x"
        "--s"
        help = "show ImageView"
        arg_type = Int
        default = 0
        "--v"
        help = "Verpose info"
        arg_type = Int
        default = 0
    end
    return parse_args(s)
end

#input_dir = "input_data"
#output_dir = "output_data"
# load a recent image 

function generate_filename()
    file_list = readdir(input_dir);
    # list all data file
    # vector of string is sorted, ascending
    if (file_list |> length == 0)
        println("No file!")
        return "";
    else
        indx_image = findall(x -> occursin("image", x), file_list)[end]
        # indx_report = findall(x -> occursin("report", x), file_list)[end]

        ## load image
        img_filename = joinpath(input_dir, file_list[indx_image])
    end
    return img_filename
end



function process_image(img_filename)

    img = Images.load(img_filename)
    # ImageView.imshow(img)

    # image size
    global img_height = size(img)[1]
    global img_width = size(img)[2]

    # preprocess, permute dims to W x H x Channel
    img_copy = Images.channelview(img) |> copy # Channel x W x H 
    img_hwc = PermutedDimsArray(img_copy, (2, 3, 1)) # H.W.C

    # convert N0f8 to float32 (max=1.0, min=0.0)
    img_hwc_f32 = Float32.(img_hwc)

    # red channel RGB
    img_hwc_f32_red = copy(img_hwc_f32)

    # HSV channel img_HSV.(img)
    img_hwc_hsv = HSV.(img)

    # Otsu thresholding  
    # thres = otsu_threshold(img_hwc_f32_red)
    img_th = ImageBinarization.binarize(img_hwc_f32_red, Otsu())

    # fixed-value thresholding
    ImageView.imshow(img_th)

    # prefer: Watershed Segmentation 
    # dist = 1 .- distance_transform(feature_transform(img_th));


end

function julia_main()::Cint
    @show parsed_args = parse_cli()
    show_img_flag = parsed_args["s"]
    filename_flag = parsed_args["f"]
    info_flag = parsed_args["v"]

    filename = generate_filename();
    process_image(filename);
    return 0;
end

if abspath(PROGRAM_FILE) == @__FILE__
    julia_main()
end

end