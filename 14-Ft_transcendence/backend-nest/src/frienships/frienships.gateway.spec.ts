import { Test, TestingModule } from '@nestjs/testing';
import { FrienshipsGateway } from './frienships.gateway';
import { FrienshipsService } from './frienships.service';

describe('FrienshipsGateway', () => {
  let gateway: FrienshipsGateway;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [FrienshipsGateway, FrienshipsService],
    }).compile();

    gateway = module.get<FrienshipsGateway>(FrienshipsGateway);
  });

  it('should be defined', () => {
    expect(gateway).toBeDefined();
  });
});
