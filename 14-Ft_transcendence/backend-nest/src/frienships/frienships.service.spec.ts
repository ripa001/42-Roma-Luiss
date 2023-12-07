import { Test, TestingModule } from '@nestjs/testing';
import { FrienshipsService } from './frienships.service';

describe('FrienshipsService', () => {
  let service: FrienshipsService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [FrienshipsService],
    }).compile();

    service = module.get<FrienshipsService>(FrienshipsService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
