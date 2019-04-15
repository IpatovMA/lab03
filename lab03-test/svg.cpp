#include "svg.h"
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg width='" << width << "' height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "' "
         << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout<< "<text x= \" "<<left<<" \" y=\" " <<baseline<<" \">"<<text<<"</text>";
}

void
svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout<< "<rect x= \" "<<x<<" \" y=\" " <<y
        <<" \" width = \" "<<width<<" \" height=\" " <<height
        <<" \" fill='"<<fill<<"' stroke='"<<stroke<<"'/>";
}

void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;

    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    max_count*=10;
    const bool scaling_needed = max_count > MAX_ASTERISK;

    double scaling_factor;
        if (scaling_needed)
        {
            scaling_factor = (double)MAX_ASTERISK / max_count;
        }


    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = 10 * bin * scaling_factor;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "#465945","#ACE1AF");
        top += BIN_HEIGHT;
    }



    svg_end();
}

void
show_histogram_svg_7var(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;

    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;


    size_t max_count=0;
    int average_in_bin=0;
    for(size_t bin: bins)
    {
        max_count =max(max_count,bin);
        average_in_bin += bin;
    }
    average_in_bin/=bins.size();

    max_count*=10;
    const bool scaling_needed = max_count > MAX_ASTERISK;

    double scaling_factor;
        if (scaling_needed)
        {
            scaling_factor = (double)MAX_ASTERISK / max_count;
        }

    const double average_width = 10*average_in_bin*scaling_factor;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (int bin : bins)
    {
        const double over_width = 10 * abs(average_in_bin-bin) * scaling_factor;
        if (bin>=average_in_bin){
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, average_width, BIN_HEIGHT);
            svg_rect(TEXT_WIDTH+average_width, top, over_width, BIN_HEIGHT,"#465945","#ACE1AF");
        } else {
            const double bin_width = 10 * bin * scaling_factor;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            svg_rect(TEXT_WIDTH+bin_width, top, over_width, BIN_HEIGHT,"#8f0000","#d67474");

        }
        top += BIN_HEIGHT;
    }



    svg_end();
}
