import Pkg
Pkg.activate(".");

using ArgParse
using FileIO
using Images
using ImageBinarization
using ImageSegmentation
using Statistics

import ImageView


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


# load a recent image 
function generate_filename()
    file_list = readdir(".//input_data");
    # list all data file
    # vector of string is sorted, ascending
    if (file_list |> length == 0)
        println("No file!")
        return "";
    else
        indx_image = findall(x -> occursin("image", x), file_list)[end]
        # indx_report = findall(x -> occursin("report", x), file_list)[end]

        ## load image
        img_filename = joinpath("input_data/", file_list[indx_image])
    end
    return img_filename
end



function process_image(img_filename)

    img = Images.load(img_filename)
    # ImageView.imshow(img)

    # image size
    img_height, img_width = size(img)

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


function main()
    @show parsed_args = parse_cli()
    show_img_flag = parsed_args["s"]
    filename_flag = parsed_args["f"]
    info_flag = parsed_args["v"]
end