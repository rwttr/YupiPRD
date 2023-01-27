module WierDetector

import Pkg
Pkg.activate(".");

using ArgParse
using FileIO
using Images
# using ImageBinarization
# using ImageSegmentation
using Statistics
using Printf
# using ImageView # Debug Only

global crop_rowpx = 350:750
global crop_colpx = 660:800

# Red- threshold value in RGB image
red_thres = 0.8

# function parse_cli()
#     s = ArgParseSettings()
#     @add_arg_table s begin
#         "--f"
#         help = "Explicitly specify image file. (default = lastest file)"
#         arg_type = String
#         default = ""
#         "--s"
#         help = "show ImageView"
#         arg_type = Int
#         default = 0
#         "--v"
#         help = "Verpose info"
#         arg_type = Int
#         default = 0
#     end
#     return parse_args(s)
# end

global input_dir = "input_data/"
global output_dir = "output_data/"

# load a recent image 
function generate_filename()
    file_list = readdir(input_dir)
    # list all data file
    # vector of string is sorted, ascending
    if (file_list |> length == 0)
        println("No file!")
        return ""
    else
        indx_image = findall(x -> occursin("image", x), file_list)[end]
        # indx_report = findall(x -> occursin("report", x), file_list)[end]

        input_img_filename = joinpath(input_dir, file_list[indx_image])
        output_img_filename = joinpath(output_dir, file_list[indx_image])
    end
    return input_img_filename, output_img_filename
end

function find_centerpx(x::Vector{CartesianIndex{2}})
    rowpx = map(x -> x.I[1], x)
    colpx = map(x -> x.I[2], x)

    left_row = minimum(rowpx)
    top_col = minimum(colpx)
    right_row = maximum(rowpx)
    bot_col = maximum(colpx)

    cen_row = (left_row + right_row) / 2 |> round |> Int
    cen_col = (top_col + bot_col) / 2 |> round |> Int

    return CartesianIndex(cen_row, cen_col)
end

function find_straightness(x::Vector{CartesianIndex{2}})
    pdist = 0.0 # consecutive pairwise px distance
    ldist = 1.0 # least L2 distance
    for i = 2:length(x)
        pdist += norm((x[i] - x[i-1]).I, 2) # p-2 norm
    end

    ldist = norm((x[1] - x[end]).I, 2)

    return pdist / ldist
end

function process_image(input_img_filename, output_img_filename)

    img = Images.load(input_img_filename)
    # ImageView.imshow(img)

    # image size
    img_height = size(img)[1]
    img_width = size(img)[2]

    # Wier Area 
    wierAreaMask = zeros(Bool, img_height, img_width)
    wierAreaMask[crop_rowpx, crop_colpx] .= 1

    # preprocess, permute dims to W x H x Channel
    img_copy = Images.channelview(img) |> copy # Channel x W x H 
    img_hwc_rgb = PermutedDimsArray(img_copy, (2, 3, 1)) # H.W.C # Red-channel

    # HSV channel img_HSV.(img)
    # img_hsv = HSV.(img)
    # img_hwc_hsv = PermutedDimsArray(Images.channelview(img_hsv), (2, 3, 1)) # H.W.C

    img_red_wier = img_hwc_rgb[:, :, 1] .* wierAreaMask
    # ImageView.imshow(img_red_wier)

    for i in eachindex(img_red_wier)
        if img_red_wier[i] >= red_thres
            img_red_wier[i] = 1
        else
            img_red_wier[i] = 0
        end
    end
    # ImageView.imshow(img_red_wier);

    # save the processed image
    save(output_img_filename[1:end-4] * "_p.jpg", colorview(Gray, img_red_wier))

    # label connected components 
    img_label = label_components(Bool.(img_red_wier))
    no_label = maximum(img_label)

    # Center px in CartesianIndex of wier pole
    label_center = CartesianIndex{2}[]

    # require 2 poles
    if (no_label < 2)
        return label_center
    end

    # put label into difference image 3-dims
    for i in 1:no_label
        activepx_label = findall(x -> x == i, img_label)
        push!(label_center, find_centerpx(activepx_label))
    end

    # poles_position = map(x -> x.I, label_center)

    return label_center
    # output : Vector{CartesianIndex}
end

function process_pole(x::Vector{CartesianIndex{2}}, output_filename)
    filename_point = replace(output_filename, "image" => "point")[1:end-4] * ".txt"
    touch(filename_point)

    poles_position = map(x -> x.I, x)

    local save_data = String("")
    save_data *= "[metrics]\n"
    # save_data *= string(find_straightness(x)) * "\n"
    save_data *= Printf.@sprintf "%.6f\n" find_straightness(x)

    save_data *= "[points]\n"
    for px in eachindex(poles_position)
        # print(string(poles_position[px])[2:end-1] * "\n")
        save_data *= string(poles_position[px])[2:end-1] * "\n"
    end

    # write to file
    file = open(filename_point, "w")
    write(file, save_data)
    close(file)
end

function julia_main()::Cint
    # @show parsed_args = parse_cli()
    # show_img_flag = parsed_args["s"]
    # filename_flag = parsed_args["f"]
    # info_flag = parsed_args["v"]

    # if (filename_flag != "")
    #     global filename
    # end

    input_filename, output_filename = generate_filename()
    centerpx_cat = process_image(input_filename, output_filename)
    if (centerpx_cat == [])
        println("aborted.")
        return 0
    end
    process_pole(centerpx_cat, output_filename)
    println("Completed.")
    return 0
end

if abspath(PROGRAM_FILE) == @__FILE__
    julia_main()
end

end