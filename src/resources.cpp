///
/// Copyright 2016 Oliver Giles
///
/// This file is part of Laminar
///
/// Laminar is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Laminar is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with Laminar.  If not, see <http://www.gnu.org/licenses/>
///
#include "resources.h"
#include <string.h>

#define INIT_RESOURCE(route, name) \
    extern const char _binary_##name##_z_start[];\
    extern const char _binary_##name##_z_end[]; \
    resources[route] = std::make_pair(_binary_ ## name ## _z_start, _binary_ ## name ## _z_end)

Resources::Resources()
{
    // TODO: Content-type
    INIT_RESOURCE("/", index_html);
    INIT_RESOURCE("/favicon.ico", favicon_ico);
    INIT_RESOURCE("/favicon-152.png", favicon_152_png);
    INIT_RESOURCE("/progress.gif", progress_gif);
    INIT_RESOURCE("/icon.png", icon_png);
    INIT_RESOURCE("/js/app.js", js_app_js);
    INIT_RESOURCE("/js/Chart.HorizontalBar.js", js_Chart_HorizontalBar_js);
    INIT_RESOURCE("/js/ansi_up.js", js_ansi_up_js);
    INIT_RESOURCE("/js/vue.min.js", js_vue_min_js);
    INIT_RESOURCE("/js/vue-router.min.js", js_vue_router_min_js);
    INIT_RESOURCE("/js/ansi_up.js", js_ansi_up_js);
    INIT_RESOURCE("/js/Chart.min.js", js_Chart_min_js);
    INIT_RESOURCE("/js/Chart.HorizontalBar.js", js_Chart_HorizontalBar_js);
    INIT_RESOURCE("/css/bootstrap.min.css", css_bootstrap_min_css);
}

inline bool beginsWith(std::string haystack, const char* needle) {
    return strncmp(haystack.c_str(), needle, strlen(needle)) == 0;
}

bool Resources::handleRequest(std::string path, const char **start, const char **end) {
    // need to keep the list of "application links" synchronised with the angular
    // application. We cannot return a 404 for any of these
    auto it = beginsWith(path,"/jobs")
            ? resources.find("/")
            : resources.find(path);

    if(it != resources.end()) {
        *start = it->second.first;
        *end = it->second.second;
        return true;
    }

    return false;
}

