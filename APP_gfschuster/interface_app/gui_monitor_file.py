import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import threading
import time
import os

ARQUIVO_LOG = "..\APP_gfschuster\qemu_output.txt"  # caminho até o arquivo de saída

class MiniEstacaoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Mini Estação Ambiental - UFSM (QEMU)")
        self.root.geometry("650x500")
        self.root.resizable(False, False)

        ttk.Label(root, text="Mini Estação Ambiental (QEMU)", font=("Segoe UI", 14, "bold")).pack(pady=10)

        self.temp_var = tk.StringVar(value="--")
        self.lux_var = tk.StringVar(value="--")
        self.hum_var = tk.StringVar(value="--")

        frame = ttk.Frame(root)
        frame.pack(pady=10)
        ttk.Label(frame, text="Temperatura (°C):").grid(row=0, column=0, padx=5, pady=5, sticky="e")
        ttk.Label(frame, textvariable=self.temp_var, font=("Segoe UI", 11, "bold")).grid(row=0, column=1, sticky="w")
        ttk.Label(frame, text="Luminosidade (lx):").grid(row=1, column=0, padx=5, pady=5, sticky="e")
        ttk.Label(frame, textvariable=self.lux_var, font=("Segoe UI", 11, "bold")).grid(row=1, column=1, sticky="w")
        ttk.Label(frame, text="Umidade (%):").grid(row=2, column=0, padx=5, pady=5, sticky="e")
        ttk.Label(frame, textvariable=self.hum_var, font=("Segoe UI", 11, "bold")).grid(row=2, column=1, sticky="w")

        ttk.Separator(root, orient="horizontal").pack(fill="x", pady=10)

        self.fig, self.ax = plt.subplots(figsize=(6, 3))
        self.canvas = FigureCanvasTkAgg(self.fig, master=root)
        self.canvas.get_tk_widget().pack()

        self.temps, self.luxes, self.hums, self.times = [], [], [], []
        self.start_time = time.time()

        threading.Thread(target=self.ler_arquivo, daemon=True).start()

    def ler_arquivo(self):
        print("Monitorando arquivo:", ARQUIVO_LOG)
        ultima_linha = ""
        while True:
            if os.path.exists(ARQUIVO_LOG):
                with open(ARQUIVO_LOG, "r", encoding="utf8") as f:
                    linhas = f.readlines()
                    if linhas:
                        linha = linhas[-1].strip()
                        if linha != ultima_linha and "," in linha:
                            ultima_linha = linha
                            try:
                                temp, lux, hum = map(int, linha.split(","))
                                self.atualizar_interface(temp, lux, hum)
                            except:
                                pass
            time.sleep(1)

    def atualizar_interface(self, temp, lux, hum):
        self.temp_var.set(str(temp))
        self.lux_var.set(str(lux))
        self.hum_var.set(str(hum))
        t = round(time.time() - self.start_time, 1)
        self.times.append(t)
        self.temps.append(temp)
        self.luxes.append(lux)
        self.hums.append(hum)
        if len(self.times) > 30:
            self.times = self.times[-30:]
            self.temps = self.temps[-30:]
            self.luxes = self.luxes[-30:]
            self.hums = self.hums[-30:]
        self.plotar()

    def plotar(self):
        self.ax.clear()
        self.ax.plot(self.times, self.temps, label="Temperatura (°C)", color="red")
        self.ax.plot(self.times, self.luxes, label="Luminosidade (lx)", color="orange")
        self.ax.plot(self.times, self.hums, label="Umidade (%)", color="blue")
        self.ax.legend(loc="upper right")
        self.ax.grid(True)
        self.ax.set_xlabel("Tempo (s)")
        self.ax.set_ylabel("Valor")
        self.canvas.draw()

if __name__ == "__main__":
    root = tk.Tk()
    app = MiniEstacaoApp(root)
    root.mainloop()
