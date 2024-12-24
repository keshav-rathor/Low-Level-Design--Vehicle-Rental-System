#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

//----------Location Class-------------------------
class Location {
public:
    string address;
    double latitude, longitude;

    Location(string addr, double lat, double lon)
        : address(addr), latitude(lat), longitude(lon) {}
};

//---------Vehicle Class----------------------------
class Vehicle {
public:
    string vehicleId;
    string type; 
    string model;
    string brand;
    double hourlyRate;
    double dailyRate;
    bool availability;
// constructor to initialise 
    Vehicle(string id, string t, string m, string b, double hr, double dr)
        : vehicleId(id), type(t), model(m), brand(b), hourlyRate(hr), dailyRate(dr), availability(true) {}

    double calculateRentalCost(int duration, string unit) 
    {
        if (unit == "hour") return duration * hourlyRate;
        else if (unit == "day") return duration * dailyRate;
        return 0.0;
    }
};

//---------Bill Class------------------------
class Bill {
public:
    string billId;
    string reservationId;
    double amount;
    bool status; 

    Bill(string id, string resId, double amt)
        : billId(id), reservationId(resId), amount(amt), status(false) {}

    void markAsPaid() 
    {
        status = true;
    }
};

//---------Payment Class-----------------------
class Payment {
public:
    string paymentId;
    string billId;
    string paymentMethod;
    bool status;

    Payment(string id, string bId, string method)
        : paymentId(id), billId(bId), paymentMethod(method), status(false) {}

    bool processPayment(double amount) 
    {
        // Simulate payment processing
        cout << "Processing payment of $ " << amount << " via " << paymentMethod << endl;
        status = true;
        return status;
    }
};

//-------Reservation Class---------------------
class Reservation {
public:
    string reservationId;
    string userId;
    string vehicleId;
    string storeId;
    string startTime;
    string endTime;
    int duration;
    string unit; // "hour" or "day"
    bool status; // true = Confirmed, false = Pending

    Reservation(string id, string uId, string vId, string sId, string start, string end, int dur, string u)
        : reservationId(id), userId(uId), vehicleId(vId), storeId(sId), startTime(start), endTime(end),
          duration(dur), unit(u), status(false) {}

    void confirmReservation() 
    {
        status = true;
    }
};

// ---------VehicleInventory Class-----------
class VehicleInventory {
public:
    string inventoryId;
    string storeId;
    vector<Vehicle> vehicles;

    VehicleInventory(string id, string sId)
    : inventoryId(id), storeId(sId) {}



    void addVehicle(Vehicle vehicle) 
    {
        vehicles.push_back(vehicle);
    }

    vector<Vehicle> getVehiclesByType(string type) 
    {
        vector<Vehicle> result;
        for (auto &vehicle : vehicles) 
        {
            if (vehicle.type == type && vehicle.availability)
                result.push_back(vehicle);
        }
        return result;
    }

    void updateAvailability(string vehicleId, bool availability) {
        for (auto &vehicle : vehicles) 
        {
            if (vehicle.vehicleId == vehicleId) 
            {
                vehicle.availability = availability;
                break;
            }
        }
    }
};

//---------Store Class--------------------------
class Store {
public:
    string storeId;
    string name;
    Location location;
    VehicleInventory inventory;

    Store(string id, string n, Location loc)
    : storeId(id), name(n), location(loc), inventory(id, n) {}

    vector<Vehicle> getVehiclesByType(string type) 
    {
        return inventory.getVehiclesByType(type);
    }
};

//---------User Class-----------------------
class User {
public:
    string userId;
    string name;
    string email;
    string phoneNumber;

    User(string id, string n, string e, string phone)
        : userId(id), name(n), email(e), phoneNumber(phone) {}

    vector<Store> searchStores(vector<Store> &stores, string location) 
    {
        vector<Store> result;
        for (auto &store : stores) 
        {
            if (store.location.address.find(location) != string::npos) result.push_back(store);
                
        }
        return result;
    }

    void makeReservation(Store &store, string vehicleType, int duration, string unit) 
    {
        vector<Vehicle> availableVehicles = store.getVehiclesByType(vehicleType);
        if (availableVehicles.empty()) 
        {
            cout << "No:--- " << vehicleType << " available at the selected store........" << endl;
            return;
        }

        Vehicle &vehicle = availableVehicles[0];
        double cost = vehicle.calculateRentalCost(duration, unit);
        cout << "Reservation Cost:-- $" << cost << endl;

        // Create a reservation..
        Reservation reservation("R1", userId, vehicle.vehicleId, store.storeId, "10:00 AM", "4:00 PM", duration, unit);
        reservation.confirmReservation();
        cout << "reservation confirmed for vehicle:----- " << vehicle.vehicleId << endl;

        // Generate bill..
        Bill bill("B1", reservation.reservationId, cost);

        // Process payment..
        Payment payment("P1", bill.billId, "Credit Card");
        if (payment.processPayment(cost)) 
        {
            bill.markAsPaid();
            cout << "Payment successful. Reservation is finalized!" << endl;
        } 
        else 
        {
            cout << "Payment failed. Reservation not confirmed." << endl;
        }

        // Update vehicle availability..
        store.inventory.updateAvailability(vehicle.vehicleId, false);
    }
};


int main() {
   
    Location loc1("Downtown, City A", 40.7128, -74.0060);
    Store store1("S1", "Downtown Rentals", loc1);
    store1.inventory.addVehicle(Vehicle("V1", "Car", "Model X", "Tesla", 10.0, 100.0));
    store1.inventory.addVehicle(Vehicle("V2", "Bike", "CBR600", "Honda", 50.0, 5000.0));

    User user1("U1", "John Doe", "john.doe@example.com", "123-456-7890");

    // User searches for stores
    vector<Store> stores = {store1};
    vector<Store> foundStores = user1.searchStores(stores, "Downtown");
    if (!foundStores.empty()) 
    {
        cout << "found store:----" << foundStores[0].name << endl;
        // User makes a reservation
        user1.makeReservation(foundStores[0], "Car", 300, "hour");
    }
    else 
    {
        cout << "No stores found at the specified location.........." << endl;
    }

    return 0;
}
