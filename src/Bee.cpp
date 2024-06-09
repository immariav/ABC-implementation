#include "Bee.h"

Bee::Bee(const int id) : id(id) {
    //create pipes
    create_named_pipes(id);
    //arm and takeoff
    
}

Bee::~Bee() {
    //destroy pipes
    close_named_pipes(id);
}

void Bee::moveToPoint(const POINT &point)
{

}

void Bee::doWaggleDance(std::vector<std::shared_ptr<FoodSource>> sourcesToShare)
{
	
}

void Bee::watchWaggleDance()
{
}

bool Bee::scanNectar()
{
	
	return false; 
}

// genenerates points for local search
std::vector<POINT> Bee::spiral_points(const POINT& center, const double step)
{
    std::vector<POINT> points;
    double angle = 0;
    double r = 0;
    while (r <= radius) {
        double x = center.x + r * cos(angle);
        double y = center.y + r * sin(angle);
        points.push_back({x, y});
        angle += step / (r != 0 ? r : step);
        r = angle * step / (2 * M_PI);
    }
    return points;
}

std::vector<POINT>& Bee::localSearch(const POINT& location, double radius)
{
    std::vector<POINT> points = spiral_points(location, radius);

    // Отправляем вектор точек в именованный канал Python
    send_vector_to_python(id, points);

    

    // Получаем результат из именованного канала Python
    std::vector<int> output_coordinates = receive_vector_from_python(id);

    // Преобразуем полученные координаты обратно в POINT и сохраняем их в выходном векторе
    std::vector<POINT> output_points;
    for (const auto& coordinate : output_coordinates) {
        POINT point;
        // Преобразуйте coordinate в POINT
        output_points.push_back(point);
    }

    return output_points;
}