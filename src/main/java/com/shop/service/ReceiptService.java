package com.shop.service;

import com.shop.model.Receipt;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * Сервиз за работа с касови бележки:
 * — запис в текстов файл
 * — четене от текстов файл
 * — сериализация (запис на обект)
 * — десериализация (зареждане на обект)
 */
public class ReceiptService {

    // Папката, в която се съхраняват файловете с бележки
    private static final String RECEIPTS_DIR = "receipts";

    public ReceiptService() {
        // Създаваме папката, ако не съществува
        try {
            Files.createDirectories(Paths.get(RECEIPTS_DIR));
        } catch (IOException e) {
            System.err.println("Грешка при създаване на папка: " + e.getMessage());
        }
    }

    /**
     * Записва касовата бележка като текстов файл.
     * Името на файла е: receipt_1.txt, receipt_2.txt и т.н.
     */
    public void saveToFile(Receipt receipt) {
        String fileName = RECEIPTS_DIR + "/receipt_" + receipt.getReceiptNumber() + ".txt";
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(receipt.toFormattedString());
            System.out.println("Бележка записана: " + fileName);
        } catch (IOException e) {
            System.err.println("Грешка при запис на бележка: " + e.getMessage());
        }
    }

    /**
     * Чете и връща съдържанието на текстов файл с бележка.
     */
    public String readFromFile(int receiptNumber) {
        String fileName = RECEIPTS_DIR + "/receipt_" + receiptNumber + ".txt";
        try {
            return Files.readString(Path.of(fileName));
        } catch (IOException e) {
            return "Грешка при четене на бележка #" + receiptNumber + ": " + e.getMessage();
        }
    }

    /**
     * Сериализира (записва като бинарен обект) касовата бележка.
     * Файлът е: receipt_1.ser, receipt_2.ser и т.н.
     */
    public void serialize(Receipt receipt) {
        String fileName = RECEIPTS_DIR + "/receipt_" + receipt.getReceiptNumber() + ".ser";
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fileName))) {
            oos.writeObject(receipt);
            System.out.println("Бележка сериализирана: " + fileName);
        } catch (IOException e) {
            System.err.println("Грешка при сериализация: " + e.getMessage());
        }
    }

    /**
     * Десериализира (зарежда от бинарен файл) касова бележка.
     */
    public Receipt deserialize(int receiptNumber) {
        String fileName = RECEIPTS_DIR + "/receipt_" + receiptNumber + ".ser";
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fileName))) {
            Receipt receipt = (Receipt) ois.readObject();
            System.out.println("Бележка десериализирана: " + fileName);
            return receipt;
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Грешка при десериализация: " + e.getMessage());
            return null;
        }
    }
}
