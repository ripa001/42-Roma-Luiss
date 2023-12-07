import {
	Controller,
	Get,
	Post,
	Body,
	Patch,
	Param,
	Delete,
	Request,
	Query,
	Res,
	UploadedFile,
	ParseFilePipe,
	MaxFileSizeValidator,
	FileTypeValidator,
	UseInterceptors,
	Put,
	HttpException,
	HttpStatus,
} from '@nestjs/common';
import * as fs from 'fs'
import * as path from 'path';//REMOVE
import { PlayersService } from './players.service';
import { CreatePlayerDto } from './dto/create-player.dto';
import { UpdatePlayerDto } from './dto/update-player.dto';
import { Response } from 'express';
import { Express } from 'express'
import { FileInterceptor } from '@nestjs/platform-express';
import { PrismaClientKnownRequestError } from '@prisma/client/runtime/library';
// import { ApiBody } from '@nestjs/swagger';

const debug = false;

@Controller('players')
export class PlayersController {
	constructor(private readonly playersService: PlayersService) {}

	// @ApiBody({
	// 	type: CreatePlayerDto,
	// 	required: true,
	// })
	@Post()
	create(@Body() createPlayerDto: CreatePlayerDto) {
		return this.playersService.create(createPlayerDto);
	}

	@Get()
	findAll() {
		return this.playersService.findAll();
	}

	@Get('me')
	async getMe(@Request() req) {
		const player = await this.playersService.findOne(Number(req.user.sub));

		if (player) {
			player.avatar = `/players/avatar/${req.user.sub}`
		}
		if (debug) console.log(`avatar address: ${player.avatar}`);

		return player;
	}

	// @Get('status/:id')
	// getUserStatus(@Param('id') id: string) : 'offline' | 'online' | 'playing' {
	// 	const status : 'offline' | 'online' | 'playing' = this.playersService.getConnection(Number(id))
	// 	if (debug) console.log(`p.controller | status : ${status}`)
	// 	return status;
	// }


	@Get('leaderboard')
	async getLeaderboard()
	{
		return await this.playersService.getLeaderboard();
	}

	@Get('avatar/:id')
	async getAvatar(@Param('id') id: string, @Res() res: Response) {
		const filePath = path.join(
			process.cwd(), (await this.playersService.findOne(Number(id)))?.avatar
		);

		fs.open(filePath, 'r', (err, fd) => {
			let returnedFilePath: string;

			if (err) {
				returnedFilePath = path.join(
					process.cwd(),
					process.env.BACKEND_DEFAULT_ONERR_PFP
				);
			}
			else {
				fs.close(fd)
				returnedFilePath = filePath;
			}
			const file = fs.createReadStream(returnedFilePath)
			res.setHeader("Content-Type", `img/${filePath.split('.')[1]}`)
			file.pipe(res)
		});
	}

	// @Get('addFriend/:username')
	// addFriend(@Body() username: string) {}

	//TODO add interface "Connection" here for return type spec
	@Get('friends/:id')
	getFriends(@Param('id') id: string, @Query('includePending') includePending: string) {
		if (debug) console.log(`PlayersController | includePending: ${Boolean(includePending)}, ${typeof Boolean(includePending)}`);
		return this.playersService.getAllFriends(Number(id), includePending === 'true' ? true : false);
	}

	@Get('publicUsers/:id')
	async getPublicUsers(@Param('id') id: string) {
		// if (debug) console.log(`CONTROLLER - getAllPublicUsers: id param = ${id}`);
		return this.playersService.getAllPublicUsers(Number(id));
	}

	@Get('pendingUsers/:id')
	async getPendingUsers(@Param('id') id: string) {
		// if (debug) console.log(`CONTROLLER - getAllPendingUsers: id param = ${id}`);
		return this.playersService.getAllPendingUsers(Number(id));
	}

	@Get('blocked')
	getAllBlockedUsers(@Request() req) {
		return this.playersService.getAllBlockedUsers(Number(req.user.sub));
	}
	

	@Get('games/:id')
	getGames(@Param('id') id: string, @Query('limit') limit: string) {
		if (debug) console.log(`CONTROLLER - getGames: id param = ${id}`);
		return this.playersService.getAllGames(
			Number(id),
			limit ? Number(limit) : undefined,
		);
	}

	@Get('achievements/:id')
	getAchievements(@Param('id') id: string) {
		if (debug) console.log(`DEBUG | players.controller | getAchievements | id: ${id}`);
		return this.playersService.getAllAchievements(Number(id));
	}

	@Get(':id')
	async findOne(@Param('id') id: string, @Request() req) {
		const userID = Number(req.user.sub);
		const player = await this.playersService.findOne(Number(id));
		const friendship = await this.playersService.getOneFriend(userID, Number(id));

		if (null == player) {
			throw new HttpException('user unknown', HttpStatus.NOT_FOUND);
		}
		if (friendship) {
			if (
				(userID == friendship.requestorID && friendship.requestor_blacklisted)
				||
				(userID == friendship.recipientID && friendship.recipient_blacklisted)
			)
				throw new HttpException('Cannot view profile of blocked user', HttpStatus.FORBIDDEN);
		}
		if (player) {
			player.avatar = `players/avatar/${player.id}`;
		}
		return player;
	}

	@Get('me/completeProfile')
	async setProfileAsComplete(@Request() req) {
		try {
			await this.playersService.setProfileAsComplete(Number(req.user.sub));
		}
		catch (err) {
			throw new HttpException(err.toString(), HttpStatus.INTERNAL_SERVER_ERROR);
		}
	}
	
	@Put('me/avatar')
	@UseInterceptors(FileInterceptor('avatar'))
	async updateAvatar(
		@Request() req,
		@UploadedFile(
			new ParseFilePipe({
				validators: [
					new MaxFileSizeValidator({ maxSize: 1024*1024*2}),
					new FileTypeValidator({ fileType: 'image/*'}),
				]
			})
		) avatar: Express.Multer.File
	) {
		const newRelPath = `${process.env.BACKEND_PFP_BASEFOLDER}${Number(req.user.sub)}_${avatar.originalname}`;
		const newfilePath = path.join(
			process.cwd(),
			newRelPath
		);

		try {
			const oldRelPath = (await this.playersService.findOne(Number(req.user.sub))).avatar;
			const oldFilePath = path.join(
				process.cwd(),
				oldRelPath
			);

			if (`${process.env.BACKEND_DEFAULT_PFP}` != oldRelPath &&
				`${process.env.BACKEND_DEFAULT_ONERR_PFP}` != oldRelPath)
				fs.unlinkSync(oldFilePath);
			await this.playersService.update(
				Number(req.user.sub),
				{avatar: newRelPath}
			);
			fs.writeFileSync(newfilePath, avatar.buffer);
		}
		catch (error) {
			throw new HttpException('Could Not Upload Avatar', HttpStatus.INTERNAL_SERVER_ERROR);
		}
	}

	@Patch('me')
	async updateMe(@Request() req, @Body() updatePlayerDto: UpdatePlayerDto)
	{
		if (debug) console.log(`DEBUG | players.controller | Patch(/player/me) : updateMe()`);
		if (debug) console.log(updatePlayerDto);
		try {
			await this.playersService.update(Number(req.user.sub), updatePlayerDto);
		}
		catch(err) {
			if (
				(err instanceof PrismaClientKnownRequestError) &&
				(err as PrismaClientKnownRequestError).code == 'P2002'
			)
				throw new HttpException(`username ${updatePlayerDto.username} is already in use`, HttpStatus.CONFLICT);
			else
				throw new HttpException('Internal Server Error', HttpStatus.INTERNAL_SERVER_ERROR);
		}
	}

	@Delete(':id')
	remove(@Param('id') id: string) {
		return this.playersService.remove(Number(id));
	}
}
