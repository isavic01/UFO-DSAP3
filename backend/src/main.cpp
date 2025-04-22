#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "UFO_Sightings.h"

using namespace Pistache;

UFO_Sightings sightings;

void topCitiesHandler(const Rest::Request& req, Http::ResponseWriter res) {
    auto year = std::stoi(req.query().get("year").value_or("0"));
    std::string output = sightings.get_top_locations("Heap", year); 
    res.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    res.send(Http::Code::Ok, output);
}

void topTimesHandler(const Rest::Request& req, Http::ResponseWriter res) {
    auto year = std::stoi(req.query().get("year").value_or("0"));
    std::string output = sightings.get_top_times("Heap", year);
    res.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    res.send(Http::Code::Ok, output);
}

void topCityTimesHandler(const Rest::Request& req, Http::ResponseWriter res) {
    auto year = std::stoi(req.query().get("year").value_or("0"));
    std::string output = sightings.get_top_locations_at_times("Heap", year);
    res.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    res.send(Http::Code::Ok, output);
}

int main() {
    sightings.parse_csv("../data/ufo_sightings.csv");

    Http::Endpoint server(Address("*:8080"));
    Rest::Router router;

    router.get("/top-cities", Rest::Routes::bind(&topCitiesHandler));
    router.get("/top-times", Rest::Routes::bind(&topTimesHandler));
    router.get("/top-city-times", Rest::Routes::bind(&topCityTimesHandler));

    server.init();
    server.setHandler(router.handler());
    server.serve();
}
