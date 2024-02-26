import discord
import time

TOKEN = "MTIwNTYwODMwMDc3NTg2NjQzMA.GZq4Uu.hxTcdzc5zRGIyZcehgU5ngmFwBVU-3Abjt8aO8"

intents = discord.Intents.default()

client = discord.Client(intents= intents)

chanel_id = 1211724337829126145

async def get_data(path):
    with open(path, "r") as txt:
        for ln, l in enumerate(txt, 1):
            if ln == 1:
                suc = int(l.strip())
            elif ln == 2:
                fai = int(l.strip())
        
        return suc, fai

async def send_stats(suc: int, fai: int):
    chanel = client.get_channel(chanel_id)

    if chanel:
        await chanel.send(f"s: {suc}, f: {fai}")
    else:
        print(chanel, chanel_id)

@client.event
async def on_ready():
    print(f"{client.user.name} has been conected")

    while True:
        su, fa = await get_data("c:/Users/Damian/Desktop/w32mfs/data/stats.txt")
        await send_stats(su, fa)
        time.sleep(30)

client.run(TOKEN)