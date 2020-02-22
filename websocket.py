import asyncio
import websockets

config = None
changed= False

async def echo(websocket, path):
    global config
    async for message in websocket:
        await websocket.send(message)
        #msg = await websocket.recv()
        config = message
        #print(message)
        if config == '{"type":"message","text":"aooo"}':
            asyncio.get_event_loop().stop()
            


asyncio.get_event_loop().run_until_complete(
    #websockets.serve(echo, '192.168.43.201', 255))
    websockets.serve(echo, '172.18.82.53', 255))
asyncio.get_event_loop().run_forever()
print(config)


#asyncio.get_event_loop().run_until_complete(
    # websockets.serve(echo, '192.168.43.201', 255))
     #websockets.serve(echo, '172.18.82.53', 255))
#count = 0
#while count<30000000:
    #count = count +1
#asyncio.get_event_loop().close()
#print(config)

def importConfig():
    asyncio.get_event_loop().run_until_complete(
    #websockets.serve(echo, '192.168.43.201', 255))
        websockets.serve(echo, '172.18.82.53', 255))
    asyncio.get_event_loop().run_forever()
    return config