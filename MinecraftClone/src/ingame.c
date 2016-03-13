/*
 * ingame.c
 *
 *  Created on: Mar 6, 2016
 *      Author: root
 */

#include "ingame.h"
#include "network.h"
#include "world.h"
#include "entity.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "globals.h"
#include "render.h"
#include "gui.h"
#include "block.h"

int running = 0;

int moveForward = 0;
int moveStrafe = 0;
float pMotionX = 0.;
float pMotionY = 0.;
float pMotionZ = 0.;
int sprinting = 0;

void loadIngame() {
loadTexturePNG(INSTALLDIR "floor.png", TX_DEFAULT, 0);

}

void ingame_tick() {
if (!running) return;
struct packet pkt;
pkt.id = PKT_PLAY_CLIENT_PLAYERPOSLOOK;
pkt.data.play_client.playerposlook.x = gs.player->x;
pkt.data.play_client.playerposlook.y = gs.player->y;
pkt.data.play_client.playerposlook.z = gs.player->z;
//printf("at: %f, %f, %f\n", gs.player->x, gs.player->y, gs.player->z);
pkt.data.play_client.playerposlook.yaw = gs.player->yaw;
pkt.data.play_client.playerposlook.pitch = gs.player->pitch;
pkt.data.play_client.playerposlook.onGround = gs.player->onGround;
writePacket(gs.conn, &pkt);
if (0) {
	float fw = moveForward * (moveForward > 0 && sprinting ? 1.5 : 1.);
	float fs = moveStrafe * (moveForward > 0 && sprinting ? 1.5 : 1.);
	float f4 = fs * fs + fw * fw;
	if (f4 > 0.0001) {
		f4 = sqrt(f4);
		if (f4 < 1.) f4 = 1.;
		float ff = 0.02 / f4;
		float f5 = sin(-gs.player->yaw * 0.017453292);
		float f6 = cos(-gs.player->yaw * 0.017453292);
		float nmx = fs * ff * f6 - fw * ff * f5;
		float nmz = fw * ff * f6 + fs * ff * f5;
		pMotionX -= nmx;
		pMotionZ += nmz;
	}
	pMotionY -= 0.02;
	gs.player->x += (pMotionX *= 0.82);
	gs.player->y += (pMotionY *= 0.90);
	if (gs.player->y < .4) {
		gs.player->y = .4;
	}
	if (gs.player->y <= .4 && pMotionY < 0.) pMotionY = 0.;
	gs.player->z += (pMotionZ *= 0.82);
	if (fabs(pMotionX) < 0.0005) pMotionX = 0.;
	if (fabs(pMotionY) < 0.0005) pMotionY = 0.;
	if (fabs(pMotionZ) < 0.0005) pMotionZ = 0.;
}
for (size_t i = 0; i < gs.world->entity_count; i++) {
	if (gs.world->entities[i] != NULL) {
		gs.world->entities[i]->lx = gs.world->entities[i]->x;
		gs.world->entities[i]->ly = gs.world->entities[i]->y;
		gs.world->entities[i]->lz = gs.world->entities[i]->z;
		gs.world->entities[i]->lyaw = gs.world->entities[i]->yaw;
		gs.world->entities[i]->lpitch = gs.world->entities[i]->pitch;
	}
}
}

//struct vao tb;
//int tbx = 0;

void drawIngame(float partialTick) {
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
gluPerspective((sprinting && moveForward > 0) ? 90 : 70., (double) width / (double) height, 0.05, 16. * 25.);
glMatrixMode (GL_MODELVIEW);
glLoadIdentity();
float ppitch = gs.player->pitch * (1. - partialTick) + gs.player->lpitch * partialTick;
float pyaw = gs.player->yaw * (1. - partialTick) + gs.player->lyaw * partialTick;
double px = gs.player->x * (1. - partialTick) + gs.player->lx * partialTick;
double py = gs.player->y * (1. - partialTick) + gs.player->ly * partialTick;
double pz = gs.player->z * (1. - partialTick) + gs.player->lz * partialTick;
float v3 = cos(-gs.player->lyaw * 0.017453292 - PI);
float v4 = sin(-pyaw * 0.017453292 - PI);
float v5 = -cos(-ppitch * 0.017453292);
float ly = sin(-ppitch * 0.017453292) + py;
float lx = px + v4 * v5;
float lz = pz + v3 * v5;
gluLookAt(px, py + 1.62, pz, lx, ly + 1.62, lz, 0., 1., 0.);
//printf("lookat: %f, %f\n", gs.player->pitch, gs.player->yaw);
//glBindTexture(GL_TEXTURE_2D, TX_DEFAULT);
//if (!tbx) {
//	struct vertex_tex *vt = NULL;
//	size_t vts = 0;
//	drawBlock(&vt, &vts, 1, 0xFF, 0., 0., 0.);
//	createVAO(vt, vts, &tb, 1, 0);
//}
//tbx++;
//glPushMatrix();
//glTranslatef(px + 2., py + 1., pz + 1.);
//glRotatef(tbx, 0., 1., 0.);
//drawQuads(&tb);
//glPopMatrix();
drawWorld(gs.world);
}

void runNetwork(struct conn* conn) {
spawnedIn = 0;
gs.conn = conn;
struct packet pkt;
struct packet rpkt;
while (1) {
	if (readPacket(conn, &pkt)) {
		printf("closed\n");
		return;
	}
	if (pkt.id == PKT_PLAY_SERVER_SPAWNOBJECT) {

	} else if (pkt.id == PKT_PLAY_SERVER_SPAWNEXPERIENCEORB) {

	} else if (pkt.id == PKT_PLAY_SERVER_SPAWNGLOBALENTITY) {

	} else if (pkt.id == PKT_PLAY_SERVER_SPAWNMOB) {

	} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPAINTING) {

	} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPLAYER) {

	} else if (pkt.id == PKT_PLAY_SERVER_ANIMATION) {

	} else if (pkt.id == PKT_PLAY_SERVER_STATISTICS) {

	} else if (pkt.id == PKT_PLAY_SERVER_BLOCKBREAKANIMATION) {

	} else if (pkt.id == PKT_PLAY_SERVER_UPDATEBLOCKENTITY) {

	} else if (pkt.id == PKT_PLAY_SERVER_BLOCKACTION) {

	} else if (pkt.id == PKT_PLAY_SERVER_BLOCKCHANGE) {

	} else if (pkt.id == PKT_PLAY_SERVER_BOSSBAR) {

	} else if (pkt.id == PKT_PLAY_SERVER_SERVERDIFFICULTY) {
		gs.difficulty = pkt.data.play_server.serverdifficulty.difficulty;
	} else if (pkt.id == PKT_PLAY_SERVER_TABCOMPLETE) {

	} else if (pkt.id == PKT_PLAY_SERVER_CHATMESSAGE) {

	} else if (pkt.id == PKT_PLAY_SERVER_MULTIBLOCKCHANGE) {

	} else if (pkt.id == PKT_PLAY_SERVER_CONFIRMTRANSACTION) {

	} else if (pkt.id == PKT_PLAY_SERVER_CLOSEWINDOW) {

	} else if (pkt.id == PKT_PLAY_SERVER_OPENWINDOW) {

	} else if (pkt.id == PKT_PLAY_SERVER_WINDOWITEMS) {

	} else if (pkt.id == PKT_PLAY_SERVER_WINDOWPROPERTY) {

	} else if (pkt.id == PKT_PLAY_SERVER_SETSLOT) {

	} else if (pkt.id == PKT_PLAY_SERVER_SETCOOLDOWN) {

	} else if (pkt.id == PKT_PLAY_SERVER_PLUGINMESSAGE) {

	} else if (pkt.id == PKT_PLAY_SERVER_NAMEDSOUNDEFFECT) {

	} else if (pkt.id == PKT_PLAY_SERVER_DISCONNECT) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYSTATUS) {

	} else if (pkt.id == PKT_PLAY_SERVER_EXPLOSION) {

	} else if (pkt.id == PKT_PLAY_SERVER_UNLOADCHUNK) {

	} else if (pkt.id == PKT_PLAY_SERVER_CHANGEGAMESTATE) {

	} else if (pkt.id == PKT_PLAY_SERVER_KEEPALIVE) {
		rpkt.id = PKT_PLAY_CLIENT_KEEPALIVE;
		rpkt.data.play_client.keepalive.key = pkt.data.play_server.keepalive.key;
		writePacket(conn, &rpkt);
	} else if (pkt.id == PKT_PLAY_SERVER_CHUNKDATA) {
		unsigned char* data = pkt.data.play_server.chunkdata.data;
		size_t size = pkt.data.play_server.chunkdata.size;
		struct chunk* chunk = pkt.data.play_server.chunkdata.continuous ? newChunk(pkt.data.play_server.chunkdata.x, pkt.data.play_server.chunkdata.z) : getChunk(gs.world, pkt.data.play_server.chunkdata.x, pkt.data.play_server.chunkdata.z);
		size_t bo = 0;
		for (int32_t x = 0; x < 16; x++) { // could be more!
			if (!(pkt.data.play_server.chunkdata.bitMask & (1 << x))) {
				continue;
			}
			if (size < 1) {
				if (pkt.data.play_server.chunkdata.continuous) free(chunk);
				goto rcmp;
			}
			unsigned char bpb = data[0];
			unsigned char bpbr = bpb;
			data++;
			size--;
			int32_t plen = 0;
			int32_t* pal = NULL;
			if (bpb == 0) {
				bpbr = 13;
			} else {
				int rx = readVarInt(&plen, data, size);
				data += rx;
				size -= rx;
				pal = malloc(sizeof(int32_t) * plen);
				for (int32_t i = 0; i < plen; i++) {
					rx = readVarInt(&pal[i], data, size);
					data += rx;
					size -= rx;
				}
			}
			int32_t bks_l;
			int rx = readVarInt(&bks_l, data, size);
			data += rx;
			size -= rx;
			bks_l *= 8;
			if (bks_l < 0 || bks_l > size || bpbr > 16) {
				if (pal != NULL) free(pal);
				if (pkt.data.play_server.chunkdata.continuous) free(chunk);
				goto rcmp;
			}
			for (size_t i = 0; i < bks_l; i += 8) {
				swapEndian(data + i, 8);
			}
			size_t bs = 4096 * bpbr;
			size_t tx = (bs + (bs % 8) + bo);
			if (tx / 8 + (tx % 8 > 0 ? 1 : 0) > bks_l) {
				if (pal != NULL) free(pal);
				if (pkt.data.play_server.chunkdata.continuous) free(chunk);
				goto rcmp;
			}
			block cv = 0;
			unsigned char cvi = 0;
			int16_t bi = 0;
			for (size_t i = bo; i < bs + bo; i++) {
				unsigned char bit = data[i / 8] & (1 << (i % 8));
				if (bit) cv |= (1 << cvi);
				cvi++;
				if (cvi == bpbr) {
					cvi = 0;
					if (bpb == 0) {
						chunk->blocks[bi & 0x0f][(bi & 0xf0) >> 4][(x * 16) + ((bi & 0xf00) >> 8)] = cv;
					} else if (plen > 0 && cv < plen) {
						chunk->blocks[bi & 0x0f][(bi & 0xf0) >> 4][(x * 16) + ((bi & 0xf00) >> 8)] = pal[cv];
					} else {
						chunk->blocks[bi & 0x0f][(bi & 0xf0) >> 4][(x * 16) + ((bi & 0xf00) >> 8)] = 0;
					}
					bi++;
					cv = 0;
				}
			}
			bo = bs % 8;
			size -= bs / 8;
			data += bs / 8;
			for (size_t i = 0; i < 4096; i++) {
				unsigned char lb = data[0];
				if (i % 2 == 0) {
					lb >>= 4;
				} else {
					lb &= 0x0f;
				}
				if (i % 2 == 0) {
					chunk->blockLight[i & 0x0f][(i & 0xf0) >> 4][(x * 8) + ((i & 0xf00) >> 8)] = lb << 4;
				} else {
					chunk->blockLight[i & 0x0f][(i & 0xf0) >> 4][(x * 8) + ((i & 0xf00) >> 9)] |= lb & 0x0f;
				}
				if (i % 2 == 1) {
					data++;
					size--;
				}
			}
			if (gs.world->dimension == 0) {
				chunk->skyLight = malloc(2048);
				for (size_t i = 0; i < 4096; i++) {
					unsigned char lb = data[0];
					if (i % 2 == 0) {
						lb >>= 4;
					} else {
						lb &= 0x0f;
					}
					if (i % 2 == 0) {
						chunk->skyLight[i / 2] = lb << 4;
					} else {
						chunk->skyLight[i / 2] |= lb & 0x0f;
					}
					if (i % 2 == 1) {
						data++;
						size--;
					}
				}
			}
		}
		if (pkt.data.play_server.chunkdata.continuous) {
			struct chunk* cc = getChunk(gs.world, pkt.data.play_server.chunkdata.x, pkt.data.play_server.chunkdata.z);
			if (cc != NULL) {
				free(cc); //remove chunk does not dereference the chunk
				removeChunk(gs.world, cc);
			}
			addChunk(gs.world, chunk);
		}
		free(pkt.data.play_server.chunkdata.data);
	} else if (pkt.id == PKT_PLAY_SERVER_EFFECT) {

	} else if (pkt.id == PKT_PLAY_SERVER_PARTICLE) {

	} else if (pkt.id == PKT_PLAY_SERVER_JOINGAME) {
		gs.difficulty = pkt.data.play_server.joingame.difficulty;
		gs.gamemode = pkt.data.play_server.joingame.gamemode;
		gs.maxPlayers = pkt.data.play_server.joingame.maxPlayers;
		gs.player = newEntity(pkt.data.play_server.joingame.eid, 0., 0., 0., ENTITY_OURPLAYER, 0., 0.);
		gs.reducedDebugInfo = pkt.data.play_server.joingame.reducedDebugInfo;
		gs.world = newWorld();
		spawnEntity(gs.world, gs.player);
		gs.world->levelType = pkt.data.play_server.joingame.levelType;
		gs.world->dimension = pkt.data.play_server.joingame.dimension;
	} else if (pkt.id == PKT_PLAY_SERVER_MAP) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYRELMOVE) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYLOOKRELMOVE) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYLOOK) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITY) {

	} else if (pkt.id == PKT_PLAY_SERVER_VEHICLEMOVE) {

	} else if (pkt.id == PKT_PLAY_SERVER_OPENSIGNEDITOR) {

	} else if (pkt.id == PKT_PLAY_SERVER_PLAYERABILITIES) {
		//todo
		if (!spawnedIn && 0) {
			rpkt.id = PKT_PLAY_CLIENT_PLUGINMESSAGE;
			rpkt.data.play_client.pluginmessage.channel = "MC|Brand";
			rpkt.data.play_client.pluginmessage.data = "vanilla/remake in C";
			rpkt.data.play_client.pluginmessage.data_size = 19;
			writePacket(conn, &rpkt);
			rpkt.id = PKT_PLAY_CLIENT_CLIENTSTATUS;
			rpkt.data.play_client.clientstatus.actionID = 0;
			writePacket(conn, &rpkt);
		}
	} else if (pkt.id == PKT_PLAY_SERVER_COMBATEVENT) {

	} else if (pkt.id == PKT_PLAY_SERVER_PLAYERLISTITEM) {

	} else if (pkt.id == PKT_PLAY_SERVER_PLAYERPOSLOOK) {
		gs.player->x = ((pkt.data.play_server.playerposlook.flags & 0x01) == 0x01 ? gs.player->x : 0.) + pkt.data.play_server.playerposlook.x;
		gs.player->y = ((pkt.data.play_server.playerposlook.flags & 0x02) == 0x02 ? gs.player->y : 0.) + pkt.data.play_server.playerposlook.y;
		gs.player->z = ((pkt.data.play_server.playerposlook.flags & 0x04) == 0x04 ? gs.player->z : 0.) + pkt.data.play_server.playerposlook.z;
		gs.player->lx = gs.player->x;
		gs.player->ly = gs.player->y;
		gs.player->lz = gs.player->z;
		gs.player->pitch = ((pkt.data.play_server.playerposlook.flags & 0x08) == 0x08 ? gs.player->pitch : 0.) + pkt.data.play_server.playerposlook.y;
		gs.player->yaw = ((pkt.data.play_server.playerposlook.flags & 0x10) == 0x10 ? gs.player->yaw : 0.) + pkt.data.play_server.playerposlook.z;

		printf("spawned in at: %f, %f, %f\n", gs.player->x, gs.player->y, gs.player->z);
		rpkt.id = PKT_PLAY_CLIENT_TELEPORTCONFIRM;
		rpkt.data.play_client.teleportconfirm.teleportID = pkt.data.play_server.playerposlook.teleportID;
		writePacket(conn, &rpkt);
		running = 1;
		spawnedIn = 1;
	} else if (pkt.id == PKT_PLAY_SERVER_USEBED) {

	} else if (pkt.id == PKT_PLAY_SERVER_DESTROYENTITIES) {

	} else if (pkt.id == PKT_PLAY_SERVER_REMOVEENTITYEFFECT) {

	} else if (pkt.id == PKT_PLAY_SERVER_RESOURCEPACKSEND) {

	} else if (pkt.id == PKT_PLAY_SERVER_RESPAWN) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYHEADLOOK) {

	} else if (pkt.id == PKT_PLAY_SERVER_WORLDBORDER) {

	} else if (pkt.id == PKT_PLAY_SERVER_CAMERA) {

	} else if (pkt.id == PKT_PLAY_SERVER_HELDITEMCHANGE) {

	} else if (pkt.id == PKT_PLAY_SERVER_DISPLAYSCOREBOARD) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYMETADATA) {

	} else if (pkt.id == PKT_PLAY_SERVER_ATTACHENTITY) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYVELOCITY) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYEQUIPMENT) {

	} else if (pkt.id == PKT_PLAY_SERVER_SETEXPERIENCE) {

	} else if (pkt.id == PKT_PLAY_SERVER_UPDATEHEALTH) {

	} else if (pkt.id == PKT_PLAY_SERVER_SCOREBOARDOBJECTIVE) {

	} else if (pkt.id == PKT_PLAY_SERVER_SETPASSENGERS) {

	} else if (pkt.id == PKT_PLAY_SERVER_TEAMS) {

	} else if (pkt.id == PKT_PLAY_SERVER_UPDATESCORE) {

	} else if (pkt.id == PKT_PLAY_SERVER_SPAWNPOSITION) {
		memcpy(&gs.world->spawnpos, &pkt.data.play_server.spawnposition.pos, sizeof(struct encpos));
	} else if (pkt.id == PKT_PLAY_SERVER_TIMEUPDATE) {

	} else if (pkt.id == PKT_PLAY_SERVER_TITLE) {

	} else if (pkt.id == PKT_PLAY_SERVER_UPDATESIGN) {

	} else if (pkt.id == PKT_PLAY_SERVER_SOUNDEFFECT) {

	} else if (pkt.id == PKT_PLAY_SERVER_PLAYERLISTHEADERFOOTER) {

	} else if (pkt.id == PKT_PLAY_SERVER_COLLECTITEM) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYTELEPORT) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYPROPERTIES) {

	} else if (pkt.id == PKT_PLAY_SERVER_ENTITYEFFECT) {

	}
	rcmp: ;
}
}
