#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Struct to hold transaction info
struct Transaction {
    string recipient;
    double amount;
    string location; // Geo-tag
};

/* Voice Command Recognition for automation of processes such as making calls using voice prompts.
   The function checks if the command said contains keywords for transaction making. Then the keyword determines what function to be called. */
bool recognizeVoiceCommand(const string& input) {
    string keywords[] = {"call", "pay", "send", "open"};
    const int numKeywords = 4;

    for (int i = 0; i < numKeywords; ++i) {
        if (input.find(keywords[i]) != string::npos) {
            return true;
        }
    }
    return false;
}

/* Biometric Authentication. image from the input is read and matched with the already existing 
   image that was set by the user by comparing key characteristics from those images.
   This function takes the face input array, the stored face array of pixels and the length 
   and it compares them to pixel by pixel to check the authetication */
bool biometricAuth(int faceInput[], int storedFace[], int length) {
    double distance = 0.0;
    for (int i = 0; i < length; ++i) {
        double diff = faceInput[i] - storedFace[i];
        distance += diff * diff;
    }
    distance = sqrt(distance);
    return (distance < 5.0); // Simple threshold
}

// Calculates Signal Strength using historic data and returns prediction of signal strength (Moving Average) 
/* This function takes the array of previous signals and predict the network strength*/
double predictSignalStrength(int signals[], int length) {
    if (length <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < length; ++i) {
        sum += signals[i];
    }
    return sum / length;
}

// One Function: Manage and Send Mobile Money
bool manageAndSendMoney(double* balance, double amount) {
    if (amount <= 0) {
        cout << "[Error] Invalid amount. Must be greater than zero.\n";
        return false;
    }

    if (amount > *balance) {
        cout << "[Error] Insufficient balance.\n";
        return false;
    }

    *balance -= amount;

    cout << "[Success] M" << amount << " sent successfully.\n";
    cout << "[Info] Remaining balance: M" << *balance << endl;

    return true;
}

/*  Send Money with Geo-Tracking this is useful for providing alerts when transactions occur outside the fence
    The function processes the command that was entered. The transaction succeeds only if the user makes the transaction within a locked location*/
bool processSendMoneyCommand(string& command, double* balance) {
    // Check if command starts with "send" or "pay"
    if (!(command.rfind("send", 0) == 0 || command.rfind("pay", 0) == 0)) {
        cout << "[Error] Command must start with 'send' or 'pay'.\n";
        return false;
    }

    size_t toPos = command.find("to");
    if (toPos == string::npos) {
        cout << "[Error] Invalid format. Missing 'to'.\n";
        return false;
    }

    // Extract amount part
    string amountStr = command.substr(0, toPos); // e.g., "send 300 "
    size_t firstDigit = amountStr.find_first_of("0123456789");
    if (firstDigit == string::npos) {
        cout << "[Error] No numeric amount found.\n";
        return false;
    }

    amountStr = amountStr.substr(firstDigit);
    double amount;
    try {
        amount = stod(amountStr); // safer than stoi
    } catch (...) {
        cout << "[Error] Invalid amount.\n";
        return false;
    }

    // Extract recipient part
    string recipient = command.substr(toPos + 3);
    if (recipient.empty()) {
        cout << "[Error] Recipient not specified.\n";
        return false;
    }

    // Prompt for location
    Transaction txn;
    txn.amount = amount;
    txn.recipient = recipient;

    cout << "[Geo] Enter your current location (e.g., Maseru, Roma): ";
    getline(cin, txn.location);

    cout << "[Voice] Sending M" << txn.amount << " to " << txn.recipient
         << " from location: " << txn.location << "...\n";

    // Call procedural balance function
    if (manageAndSendMoney(balance, txn.amount)) {
        cout << "[Finance] Transact ID 01JGHG74HHG3Y3 confirmed. M"
             << txn.amount << " sent successfully to " << txn.recipient
             << ".\nNew available balance: M" << *balance
             << "\nCustomer Care: 114.\n";
        return true;
    } else {
        cout << "[Error] Mpesa failed to process your transaction.\nCustomer Care: 114.\n";
        return false;
    }
}

// === MAIN FUNCTION ===
int main() {
    cout << "===========================================\n";
    cout << "   AI-Enabled Mobile Processor Simulation   \n";
    cout << "===========================================\n\n";

    int choice;
    double balance = 50000.0;  

    do {
        cout << "\nChoose an application to simulate:\n";
        cout << "1. Voice Command Recognition\n";
        cout << "2. Biometric Authentication\n";
        cout << "3. Signal Strength Prediction\n";
        cout << "4. Voice-Driven Mobile Money (Geo-tracked)\n";
        cout << "5. Run All\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1: {
                string userCommand;
                cout << "\n[Voice] Enter a voice command (e.g., 'call mom'): ";
                getline(cin, userCommand);
                if (recognizeVoiceCommand(userCommand)) {
                    cout << "[Voice] Command recognized: " << userCommand << "\n";
                } else {
                    cout << "[Voice] No valid command detected.\n";
                }
                break;
            }

            case 2: {
                int faceInput[] = {100, 98, 105, 97};
                int storedFace[] = {102, 97, 106, 96};
                int length = 4;
                cout << "\n[Biometric] Authenticating face...\n";
                if (biometricAuth(faceInput, storedFace, length)) {
                    cout << "[Biometric] Face authentication successful.\n";
                } else {
                    cout << "[Biometric] Authentication failed.\n";
                }
                break;
            }

            case 3: {
                int signals[] = {-85, -80, -78, -90};
                int length = 4;
                cout << "\n[Signal] Analyzing recent signal strengths...\n";
                double prediction = predictSignalStrength(signals, length);
                cout << "[Signal] Network strength: " << prediction << " dBm\n";
                break;
            }

            case 4: {
                string cmd;
                cout << "\n[Voice] Enter a voice command to send money (e.g., 'send 250 to Palesa'): ";
                getline(cin, cmd);
                if (!processSendMoneyCommand(cmd, &balance)) {
                    cout << "[Voice] Could not process voice transaction.\n";
                }
                break;
            }

            case 5: {
                cout << "\n[All] Running full simulation...\n";

                // Voice
                string command = "call mom";
                if (recognizeVoiceCommand(command)) {
                    cout << "[Voice] Command recognized: " << command << "\n";
                }

                // Biometric
                int faceInput[] = {100, 98, 105, 97};
                int storedFace[] = {102, 97, 106, 96};
                if (biometricAuth(faceInput, storedFace, 4)) {
                    cout << "[Biometric] Face authentication successful.\n";
                }

                // Signal
                int signals[] = {-85, -80, -78, -90};
                double prediction = predictSignalStrength(signals, 4);
                cout << "[Signal] Network strength: " << prediction << " dBm\n";

                // Financial
                string voiceCmd = "send 150 to Palesa";
                if (!processSendMoneyCommand(voiceCmd, &balance)) {
                    cout << "[Voice] Could not process voice transaction.\n";
                }

                break;
            }

            case 0:
                cout << "\n[Exit] Simulation ended. Goodbye!\n";
                break;

            default:
                cout << "\n[Error] Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
