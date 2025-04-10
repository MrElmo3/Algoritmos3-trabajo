#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>

#include "DHeap.h"

std::vector<int> BRANCHING_FACTORS = {2, 3, 4, 5, 6, 7, 8, 9, 10};

class DHeapTest : public ::testing::Test {};

std::string noErrorMsg;
std::string expectedMsg;
std::string differentErrorMsg;

// Prueba de inicialización de heap vacío
TEST_F(DHeapTest, Init) {

	// Prueba de inicializacion de heap vacio
	DHeap heap({}, {} , 2);
	EXPECT_EQ(heap.GetSize(), 0);

	// Prueba de inicialización solo con branching factor
	noErrorMsg = "Se esperaba una excepción std::invalid_argument";
	differentErrorMsg = "Se lanzo una excepción distinta a std::invalid_argument";
	std::vector<int> invalidFactors = {1, 0, -1};
	for(int b : invalidFactors) {
		expectedMsg = 
			"El factor de ramificación (" + 
			std::to_string(b) + 
			") debe ser mayor que 1.";
		try {
			DHeap heap({}, {}, b);
			FAIL() << noErrorMsg;
		} catch (const std::invalid_argument& e) {
			EXPECT_STREQ(e.what(), expectedMsg.c_str());
		} catch (...) {
			FAIL() << differentErrorMsg;
		}
	}

    // Prueba de inconsistencia entre la longitud de la lista de elementos y la lista de prioridades.
    expectedMsg = "La longitud de la lista de elementos (0) debe coincidir con la longitud de la lista de prioridades (1)";
	noErrorMsg = "Expected std::invalid_argument";
    try {
        DHeap heap({}, {1.0}, 2);
        FAIL() << noErrorMsg;
    } catch (const std::invalid_argument& e) {
        EXPECT_EQ(std::string(e.what()), expectedMsg);
    } catch (...) {
        FAIL() << differentErrorMsg;
    }
    

    // Prueba de inicialización con elementos y prioridades válidos.
    std::vector<std::any> elements = {"A", "B", "C", "D"};

	std::vector<float> priorities = {0.1f, -0.1f, 1.0f, -2.0f};

	DHeap heap2(elements, priorities, 2);
	EXPECT_EQ(heap2.GetSize(), 4);
	EXPECT_TRUE(heap2.Validate());
}

// Prueba del uso de Heapify
TEST_F(DHeapTest, Heapify) {

	for(int b : BRANCHING_FACTORS) {
		// Se genera un tamaño aleatorio para el heap
		int size = 4 + rand() % 21;
		
		std::vector<std::any> elements(size);
		for(int i = 65; i < 65 + size; i++) {
			elements[i - 65] = static_cast<char>(i);
		}

		std::vector<float> priorities(size);
		for(int i = 0; i < size; i++) {
			priorities[i] = rand() % size;
		}
		
		//  Se generan elementos (letras) y prioridades aleatorias
		DHeap heap(elements, priorities, b);
		EXPECT_EQ(heap.GetSize(), size);
		EXPECT_TRUE(heap.Validate());
	}
}

// Prueba del comportamiento en heaps vacíos y tras insertar elementos.
TEST_F(DHeapTest, Clear) {
	for (int b: BRANCHING_FACTORS) {
		DHeap heap({}, {}, b);

		// Se verifica que llamar a peek en un heap vacío arroja RuntimeError.
		expectedMsg = "Heap is empty.";
		noErrorMsg = "Expected std::out_of_range";
		try {
			heap.Peek();
			FAIL() << noErrorMsg;
		} catch (const std::out_of_range& e) {
			EXPECT_STREQ(e.what(), expectedMsg.c_str());
		}

		// Inserta el primer elemento con una prioridad muy baja.
		expectedMsg = "First";
		heap.Insert("First", -1e14);
		EXPECT_STREQ(std::any_cast<const char*>(heap.Peek()), expectedMsg.c_str());

		// Inserta varios elementos con distintas prioridades.
		heap.Insert("b", 0);
		heap.Insert("c", 0.99);
		heap.Insert("second", 1);
		heap.Insert("a", -11);

		expectedMsg = "second";
		EXPECT_STREQ(std::any_cast<const char*>(heap.Peek()), expectedMsg.c_str());
	}
}

// Prueba de inserción de elementos
TEST_F(DHeapTest, InsertTop) {
	for(int b : BRANCHING_FACTORS) {
		DHeap heap ({}, {}, b);
		try{
			heap.Top();
			FAIL() << "Expected std::out_of_range";
		} catch (const std::out_of_range& e) {
			EXPECT_STREQ(e.what(), "Heap is empty.");
		}
		
		// Prueba de top para una prioridad muy baja
		heap.Insert("First", -1e14);
		EXPECT_STREQ(std::any_cast<const char*>(heap.Top()), "First");
		EXPECT_TRUE(heap.IsEmpty());
	
		// Prueba de top para varios elementos
		heap.Insert("b", 0);
		heap.Insert("c", 0.99);
		heap.Insert("second", 1);
		heap.Insert("a", -11);
		EXPECT_STREQ(std::any_cast<const char*>(heap.Top()), "second");
		EXPECT_EQ(heap.GetSize(), 3);
	
		// Insercion de elementos con prioridades aleatorias
		for (size_t i = 0; i < 10; i++) {
			heap.Insert(std::to_string(i), (float)(rand() / (float)RAND_MAX));
		}

		while (!heap.IsEmpty()) {
			EXPECT_TRUE(heap.Validate());
			heap.Top();
		}
	}

}
