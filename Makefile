BUILD_DIR := build
BIN := $(BUILD_DIR)/rpg_app

.PHONY: all roda verifica limpa

all:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

roda: all
	./$(BIN)

verifica: all
	@echo "Executando verificacao..."
	@OUT=$$(./$(BIN)); \
	echo "$$OUT"; \
	LAST_LINE=$$(echo "$$OUT" | tail -n 1); \
	if [ "$$LAST_LINE" = "vivos=0" ]; then \
		echo "[OK] Portao passou: ultima linha e vivos=0"; \
	else \
		echo "[ERRO] Esperado 'vivos=0', obtido '$$LAST_LINE'"; \
		exit 1; \
	fi

limpa:
	rm -rf $(BUILD_DIR)