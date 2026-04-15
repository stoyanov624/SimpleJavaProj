package com.shop.service;

import com.shop.model.Receipt;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ReceiptService {

    private static final String RECEIPTS_DIR = "receipts";

    public ReceiptService() {
        createReceiptsDir();
    }

    public void saveToFile(Receipt receipt) {
        String path = filePath(receipt.getReceiptNumber(), "txt");
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(path))) {
            writer.write(receipt.toFormattedString());
            System.out.println("Бележка записана: " + path);
        } catch (IOException e) {
            System.err.println("Грешка при запис: " + e.getMessage());
        }
    }

    public String readFromFile(int receiptNumber) {
        try {
            return Files.readString(Path.of(filePath(receiptNumber, "txt")));
        } catch (IOException e) {
            return "Грешка при четене на бележка #" + receiptNumber + ": " + e.getMessage();
        }
    }

    public void serialize(Receipt receipt) {
        String path = filePath(receipt.getReceiptNumber(), "ser");
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(path))) {
            oos.writeObject(receipt);
            System.out.println("Сериализирана: " + path);
        } catch (IOException e) {
            System.err.println("Грешка при сериализация: " + e.getMessage());
        }
    }

    public Receipt deserialize(int receiptNumber) {
        String path = filePath(receiptNumber, "ser");
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(path))) {
            Receipt receipt = (Receipt) ois.readObject();
            System.out.println("Десериализирана: " + path);
            return receipt;
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Грешка при десериализация: " + e.getMessage());
            return null;
        }
    }

    private String filePath(int number, String extension) {
        return RECEIPTS_DIR + "/receipt_" + number + "." + extension;
    }

    private void createReceiptsDir() {
        try {
            Files.createDirectories(Paths.get(RECEIPTS_DIR));
        } catch (IOException e) {
            System.err.println("Грешка при създаване на папка: " + e.getMessage());
        }
    }
}
