# Low-Level-Design--Vehicle-Rental-System
### Problem Statement

The Vehicle Rental System acts as a connector between customers and rental agencies, offering a seamless and efficient rental experience. With an intuitive user interface and a robust backend, the system allows customers to effortlessly search for available vehicles, make reservations, and complete transactions.

### Requirements

1. The system should support vehicle rentals for Cars and Bikes, with the flexibility to add other vehicle types in the future.
2. Users must be able to search for rental stores based on location.
3. Users should have the ability to view all available vehicles of a specific type from a chosen store.
4. Users can reserve a vehicle of their choice from the inventory.
5. Vehicles can be rented on a daily or hourly basis.
6. To confirm a reservation, users must pay the associated bill.

### Key Objects

- **User**: Represents customers interacting with the system.
- **Store**: Represents a rental agency offering vehicles.
- **Location**: Denotes the geographical location of a store.
- **Vehicle**: Represents the rentable assets (e.g., Cars, Bikes).
- **Reservation**: Tracks booking details for a specific vehicle.
- **Bill**: Details the payment amount for a reservation.
- **Payment**: Handles payment processing for reservations.
- **VehicleInventory**: Manages the store's vehicle collection and availability.
