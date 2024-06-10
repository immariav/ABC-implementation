#include "Bee.h"

Bee::Bee(const int id) : id(id) {
    // Initialize Python interpreter
    Py_Initialize();

    // Add the current directory to the Python path
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");

    // Import the module containing DroneController class
    PyObject* pModule = PyImport_ImportModule("drone_controller.py");
    
    if (!pModule) {
        PyErr_Print();
        throw std::runtime_error("Failed to import module");
    }

    // Check if the module was imported successfully
    if (pModule) {
        // Get a reference to the DroneController class
        PyObject* pClass = PyObject_GetAttrString(pModule, "DroneController");
       
        if (!pClass || !PyCallable_Check(pClass)) {
            PyErr_Print();
            throw std::runtime_error("Failed to get class DroneController");
        }

        // Check if the class was obtained successfully and is callable
        if (pClass && PyCallable_Check(pClass)) {
            // Create an instance of the DroneController class
            pDroneControllerInstance = PyObject_CallObject(pClass, NULL);
            
            if (!pDroneControllerInstance) {
                PyErr_Print();
                throw std::runtime_error("Failed to create instance of DroneController");
            }
            // Check if the instance was created successfully
            if (pDroneControllerInstance) {
                // Call the connect method of the DroneController instance
                PyObject* pConnectMethod = PyObject_GetAttrString(pDroneControllerInstance, "connect");
                if (pConnectMethod && PyCallable_Check(pConnectMethod)) {
                    PyObject* pResult = PyObject_CallObject(pConnectMethod, NULL);
                    if (!pResult) {
                        PyErr_Print();  // Вывод подробной информации об ошибке
                        Py_XDECREF(pConnectMethod);
                        throw std::runtime_error("Failed to call method 'connect'");
                    }
                    Py_DECREF(pResult);
                } else {
                    PyErr_Print();  // Вывод подробной информации об ошибке
                    Py_XDECREF(pConnectMethod);
                    throw std::runtime_error("Failed to get method 'connect' or method is not callable");
                }
                // Call the arm_and_takeoff method of the DroneController instance
                PyObject* pArmAndTakeoffMethod = PyObject_GetAttrString(pDroneControllerInstance, "arm_and_takeoff");
                if (pArmAndTakeoffMethod && PyCallable_Check(pArmAndTakeoffMethod)) {
                    // Call the arm_and_takeoff method with the desired arguments
                    PyObject* pArgs = PyTuple_Pack(1, PyFloat_FromDouble(height)); // Example arguments
                    PyObject_CallObject(pArmAndTakeoffMethod, pArgs);
                    Py_DECREF(pArgs);
                }
                Py_XDECREF(pArmAndTakeoffMethod);
            }
            Py_DECREF(pClass);
        }
        Py_DECREF(pModule);
    }
}

Bee::~Bee() {
    // Finalize Python interpreter and release the Python object
    if (pDroneControllerInstance) {
        Py_DECREF(pDroneControllerInstance);
    }
    Py_Finalize();
}

void Bee::moveToPoint(const POINT point) {
    if (pDroneControllerInstance) {
        // Получить метод goto
        PyObject* pGotoMethod = PyObject_GetAttrString(pDroneControllerInstance, "goto");
        
        // Проверка, что метод существует и является вызываемым
        if (!pGotoMethod || !PyCallable_Check(pGotoMethod)) {
            PyErr_Print();
            Py_XDECREF(pGotoMethod);
            throw std::runtime_error("Failed to get method goto or method is not callable");
        }

        // Создание аргументов для вызова метода
        PyObject* pArgs = PyTuple_Pack(2, PyFloat_FromDouble(point.x), PyFloat_FromDouble(point.y));
        
        // Вызов метода goto
        PyObject* pResult = PyObject_CallObject(pGotoMethod, pArgs);
        
        // Проверка на ошибки после вызова метода
        if (!pResult) {
            PyErr_Print();
            Py_DECREF(pArgs);
            Py_XDECREF(pGotoMethod);
            throw std::runtime_error("Failed to call method goto");
        }

        // Освобождение памяти
        Py_DECREF(pArgs);
        Py_DECREF(pResult);
        Py_XDECREF(pGotoMethod);
    }
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

std::vector<POINT> Bee::getActualSources(const std::string &filename)
{
    std::vector<POINT> coordinates;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        double x, y;
        if (iss >> x >> y) {
            coordinates.push_back({x, y});
        }
    }
    return coordinates;
}

std::vector<POINT> Bee::localSearch(const POINT& location, double radius) {
    // Читаем координаты из файла
    std::vector<POINT> sources_locations = getActualSources("actualSources.txt");

    std::vector<POINT> spiral_coordinates = spiral_points(location, radius);
    std::vector<POINT> output_points;

    if (pDroneControllerInstance) {
        // Получить метод local_search
        PyObject* pLocalSearchMethod = PyObject_GetAttrString(pDroneControllerInstance, "local_search");
        if (pLocalSearchMethod && PyCallable_Check(pLocalSearchMethod)) {
            // Преобразовать аргументы
            PyObject* pSpiralList = PyList_New(spiral_coordinates.size());
            for (size_t i = 0; i < spiral_coordinates.size(); ++i) {
                PyObject* pPoint = PyTuple_Pack(2, PyFloat_FromDouble(spiral_coordinates[i].x), PyFloat_FromDouble(spiral_coordinates[i].y));
                PyList_SetItem(pSpiralList, i, pPoint);
            }
            PyObject* pSourcesList = PyList_New(sources_locations.size());
            for (size_t i = 0; i < sources_locations.size(); ++i) {
                PyObject* pPoint = PyTuple_Pack(2, PyFloat_FromDouble(sources_locations[i].x), PyFloat_FromDouble(sources_locations[i].y));
                PyList_SetItem(pSourcesList, i, pPoint);
            }

            // Создать аргументы для вызова метода
            PyObject* pArgs = PyTuple_Pack(2, pSpiralList, pSourcesList);

            // Вызвать метод local_search
            PyObject* pResult = PyObject_CallObject(pLocalSearchMethod, pArgs);

            // Освободить память
            Py_DECREF(pSpiralList);
            Py_DECREF(pSourcesList);
            Py_DECREF(pArgs);

            // Обработать результат
            if (pResult) {
                for (Py_ssize_t i = 0; i < PyList_Size(pResult); ++i) {
                    PyObject* pCoord = PyList_GetItem(pResult, i);
                    double x = PyFloat_AsDouble(PyTuple_GetItem(pCoord, 0));
                    double y = PyFloat_AsDouble(PyTuple_GetItem(pCoord, 1));
                    output_points.push_back({x, y});
                }
                Py_DECREF(pResult);
            }
        }
        Py_XDECREF(pLocalSearchMethod);
    }

    return output_points;
}

